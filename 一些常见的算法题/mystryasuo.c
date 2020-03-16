#include <stdio.h>
#include <string.h>

//aabbcce转换为a2b2c2e1
char* mystrcg(char *buf,const char *a)
{
    if(a==NULL)
    {
        return NULL;
    }
    int k=1;
    int m=0;
    int len=strlen(a);
    //int size=len*2+1;
   // char buf[size];
    for(int i=1;i<=len;++i)
    {
        if(a[i]==a[i-1])
        {
            k++;
        }
        else if(a[i]!=a[i-1])
        {
            buf[m++]=a[i-1];
            buf[m++]=k+'0';
            k=1;
        }
        else if(a[i]=='\0')
        {
            buf[m++]=a[i-1];
            buf[m++]=k+'0';
            k=1;
        }
    }
    buf[m]='\0';
    return buf;
    
}


int main()
{
    char buf[50];
    char str[]="asdssss";
    mystrcg(buf,str);
    printf("%s",buf);

    return 0;
}
