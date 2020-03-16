#include <stdio.h>
#include <string.h>

//整数转字符串
int myitoa(int a,char *str)
{
    char *buf=str;
    int temp=0;
    int left=0;
    int right;
    if(a<0)
    {
        *buf++='-';
    }
    else if(a==0)
    {
        *buf++='0';
    }
    while(a!=0)
    {
        temp=a%10;
        a=a/10;
        *buf=temp+'0';
        buf++;
    }
    *buf='\0';
    right=strlen(str)-1;
    if(str[0]=='-')
    {
        left++;
    }
    while(left<right)
    {
        {
            char tp=str[left];
            str[left]=str[right];
            str[right]=tp;
            left++;
            --right;
        }
    }
    return 0;
}


int main()
{
    int a=12312321;
    char str[100]="";
    myitoa(a,str);
    int b=strlen(str);
    printf("a:%s",str);

    return 0;
}
