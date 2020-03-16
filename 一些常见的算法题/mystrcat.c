#include <stdio.h>
#include <string.h>

//整数转字符串
char* mystrcat(char *a,const char *str)
{
    char *temp=a;
    const char *temp2=str;
    if(a==NULL||str==NULL)
    {
        return NULL;
    }
    while(*temp!='\0')
    {
        temp++;
    }
    while(*temp2!='\0')
    {
        *temp++=*temp2++;
    }
    *temp='\0';
    return a;
}


int main()
{
    char a[]="ABC";
    char str[]="123";
    mystrcat(a,str);
    printf("%s",a);

    return 0;
}
