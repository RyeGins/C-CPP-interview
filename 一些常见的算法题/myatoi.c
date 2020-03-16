#include <stdio.h>
#include <string.h>

//字符串转整数
long myatoi(const char *a)
{
    int len=strlen(a);
    long num=0;
    int flag=1;
    for(int i=0;i<len;++i)
    {
        if(a[i]==' ')
        {
            continue;
        }
        else if(a[i]<'0'||a[i]>'9')
        {
            if(num>0)
            {
                printf("未知字符串");
                return -1;
            }
            else if(a[i]=='-')
            {
                flag=-1;
            }
            else if(a[i]=='+')
            {
                flag=1;
            }
            else
            {
                printf("未知字符串");
                return -1;
            }
        }
        else
        {
            
            num=num*10+a[i]-'0';
        }
    }
    return num*flag;

}


int main()
{
    char *a="12312s";
    //char *b="-123";
    //char *c="  22";
    //char *d="ss1";
    //char *e="22-1";
    //char *f="21f";
    int A=myatoi(a);
    //long b=myatoi(b);
    //long c=myatoi(c);
    //long d=myatoi(d);
    //long e=myatoi(e);
    //long f=myatoi(f);
    printf("%d",A);

    

    return 0;
}