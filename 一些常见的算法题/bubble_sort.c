#include <stdio.h>

void bubble_sort (int a[],int len)
{
    int i=0;
    int j=0;
    int temp=0;
    int exchange=0;
    for(i=0;i<len-1;++i)
    {
        exchange=0;
        for(j=0;j<len-i-1;++j)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j+1];
                a[j+1]=a[j];
                a[j]=temp;
                exchange=1;
            }
            
        }
        
        if(exchange!=1)
        {
            return;
        }
    }
}

int main()
{
    int a[]={22,33,41,1,544,6,78,8,10};
    bubble_sort(a,9);
    for(int i=0;i<9;++i)
    {
        printf("%d \n",a[i]);
    }

    return 0;
}