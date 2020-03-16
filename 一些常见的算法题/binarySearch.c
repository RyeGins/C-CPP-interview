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

int binary_search(int *p,int key,int len)
{
    int mid, low, high;
    low = 0;
    high = len-1;
    mid = low+(high-low)/2;
    while(low<high)
    {
        if(key==p[mid])
            return mid;
        else if(key>p[mid])
        {
            low=mid+1;
            mid=low+(high-low)/2;
        }
        else if(key<p[mid])
        {
            high=mid-1;
            mid=low+(high-low)/2;
        }
    }
    return -1;
}

//递归法
int binary_search2(int *p,int key,int low,int high)
{
    int mid;
    mid = low+(high-low)/2;
    if(low<high)
    {
        if(key==p[mid])
            return mid;
        else if(key>p[mid])
        {
            return binary_search2(p,key,mid+1,high);
        }
        else if(key<p[mid])
        {
           return binary_search2(p,key,low,mid-1);
        }
    }
    return -1;
}




int main()
{
    int a[]={22,33,41,1,544,6,78,8,10};
    bubble_sort(a,9);
    for(int i=0;i<9;++i)
    {
        printf("%d \n",a[i]);
    }
    int bs = binary_search2(a,41,0,8);
    printf("41在数组中的序号是：%d\n",bs);
    return 0;
}
