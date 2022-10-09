//Question 2: Write a c program for implement of linear search


#include<stdio.h>
int main()
{
    int i, arr[50],n,key,flag;
    flag=0;
    printf("Enter the number of elements you want to enter: ");
    scanf("%d",&n);
    printf("Enter %d the elements in sorted order:\n",n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);

    }
    printf("Enter the element to be searched ");
    scanf("%d",&key);
    for(i=0;i<n;i++)
    {
        if(arr[i]==key)
        {
            printf("Found the element %d at position %d ",key,i+1);
            flag++;
            break;
        }
    }
    if(flag==0)
    {
        printf("Haven't found the element ");
    }
}