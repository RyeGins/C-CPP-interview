#include <stdio.h>

//1.求1-100之间的所有质数
int zhishu(int a[],int len)
{
    int k=0;
    a[k++]=1;
    if(len<50)
    {
        printf("传入数组过小");
        return -1;
    }
    for(int i=1;i<100;++i)
    {
        for(int j=2;j<i;++j)
        {
            if(i%j==0)
            {
                break;
            }
            else if(j==i-1)
            {
                a[k++]=i;
            }
        }

    }
    return k;

}


int main()
{
    int a[50];
    int k=zhishu(a,sizeof(a)/sizeof(int));
    printf("质数：");
    for(int i=0;i<k;++i)
    {
        printf("%d ",a[i]);
    }
    printf("\n质数个数:%d",k);
    

    return 0;
}