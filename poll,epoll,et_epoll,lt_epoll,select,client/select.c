#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main()
{
    // 1.创建套接字
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1)
    {
        perror("socket");
        exit(0);
    }
    // 2. 绑定 ip, port
    struct sockaddr_in addr;
    addr.sin_port = htons(10000);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        perror("bind");
        exit(0);
    }
    // 3. 监听
    ret = listen(lfd, 100);
    if(ret == -1)
    {
        perror("listen");
        exit(0);
    }
    
    // 4. 等待连接 -> 循环
    // 检测 -> 读缓冲区, 委托内核去处理
    // 数据初始化, 创建自定义的文件描述符集
    fd_set rdset, tmp; 
    FD_ZERO(&rdset);
    FD_SET(lfd, &rdset);
    int maxfd = lfd;
    while(1)
    {
        // 委托内核检测
        tmp = rdset;
        ret = select(maxfd+1, &tmp, NULL, NULL, NULL);
        if(ret == -1)
        {
            perror("select");
            exit(0);
        }

        // 检测的度缓冲区有变化
        // 有新连接
        if(FD_ISSET(lfd, &tmp))
        {
            // 接收连接请求
            struct sockaddr_in sockcli;
            int len = sizeof(sockcli);
            // 这个accept是不会阻塞的
            int connfd = accept(lfd, (struct sockaddr*)&sockcli, &len);
            // 委托内核检测connfd的读缓冲区
            FD_SET(connfd, &rdset);
            maxfd = connfd > maxfd ? connfd : maxfd;
        }
        // 通信, 有客户端发送数据过来
        for(int i=lfd+1; i<=maxfd; ++i)
        {
            // 如果在集合中, 说明读缓冲区有数据
            if(FD_ISSET(i, &tmp))
            {
                char buf[128];
                int ret = read(i, buf, sizeof(buf));
                if(ret == -1)
                {
                    perror("read");
                    exit(0);
                }
                else if(ret == 0)
                {
                    printf("对方已经关闭了连接...\n");
                    FD_CLR(i, &rdset);
                    close(i);
                }
                else
                {
                    printf("客户端say: %s\n", buf);
                    write(i, buf, strlen(buf)+1);
                }
            }
        }
    }
    
    close(lfd);

    return 0;
}
