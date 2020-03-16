#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

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

    // 创建epoll树
    int epfd = epoll_create(1000);
    if(epfd == -1)
    {
        perror("epoll_create");
        exit(0);
    }

    // 将监听lfd添加到树上
    struct epoll_event ev;
    // 检测事件的初始化
    ev.events = EPOLLIN ;
    ev.data.fd = lfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);

    struct epoll_event events[1024];
    // 开始检测
    while(1)
    {
        int nums = epoll_wait(epfd, events, sizeof(events)/sizeof(events[0]), -1);
        printf("numbers = %d\n", nums);
        
        // 遍历状态变化的文件描述符集合
        for(int i=0; i<nums; ++i)
        {
            int curfd = events[i].data.fd;
            // 有新连接
            if(curfd == lfd)
            {
                struct sockaddr_in clisock;
                int len = sizeof(clisock);
                int connfd = accept(lfd, (struct sockaddr*)&clisock, &len);
                if(connfd == -1)
                {
                    perror("accept");
                    exit(0);
                }
                // 将通信的fd挂到树上
                //ev.events = EPOLLIN | EPOLLOUT;
                // 设置为边沿触发
                // 设置fd属性为非阻塞
                int flag = fcntl(connfd, F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(connfd, F_SETFL, flag);

                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd  = connfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
            }
            // 通信
            else
            {
                // 读事件触发, 写事件触发
                if(events[i].events & EPOLLOUT) 
                {
                    continue;
                }

                char buf[5];
                int count = 0;
                while( (count = read(curfd, buf, sizeof(buf))) > 0)
                {
                    // 处理read数据
                    write(STDOUT_FILENO, buf, count);
                    // 直接发送回客户端
                    write(curfd, buf, count);
                }

                if(count == 0)
                {
                    printf("client disconnect...\n");
                }
                else if(count == -1)
                {
                    if(errno == EAGAIN)
                    {
                        printf("date over....\n");
                    }
                    else
                    {
                        perror("read");
                        exit(0);
                    }
                }

#if 0
                char buf[5];
                int count = read(curfd, buf, sizeof(buf));
                if(count == 0)
                {
                    printf("client disconnect ...\n");
                    close(curfd);
                    // 从树上删除该节点
                    epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
                }
                else if(count == -1)
                {
                    perror("read");
                    exit(0);
                }
                else
                {
                    // 正常情况
                    //printf("client say: %s\n", buf);
                    write(STDOUT_FILENO, buf, count);
                    write(curfd, buf, strlen(buf)+1);
                }
#endif
            }
        }
    }
    
    close(lfd);

    return 0;
}
