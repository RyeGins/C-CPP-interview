#include <stdio.h>

void quick_sort(int a[],int low,int high)
{
    int i=low;
    int j=high;
    int key=a[low];

    if(low<high)
    {
        while(i<j)
        {
            while(i<j&&key<=a[j])
            {
                    --j;
            }

            if(i<j)
            a[i++]=a[j];

            while(i<j&&key>=a[i])
            {
                    ++i;
            }
            if(i<j)
            a[j--]=a[i];
        }

        a[i]=key;
        quick_sort(a,low,i-1);
        quick_sort(a,i+1,high);


    }

}

int main()
{
    int data[]={22,31,2,444,5,66,77};
    quick_sort(data,0,6);
    for(int i=0;i<7;++i)
    {
            printf("%d \n",data[i]);

    }

}
