#include<iostream>
#include<omp.h>
using namespace std;

void parallel_bubble_sort(int arr[],int n)
{
    for(int i = 0;i<n;i++)
    {
        #pragma omp parallel for
        for(int j= 0;j<n-1;j= j+2)
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j+1],arr[j]);
            }
        }
        #pragma omp parallel for
        for(int j= 1;j<n-1;j= j+2)
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j+1],arr[j]);
            }
        }
    }
}

int main()
{
    int n;
    cout<<"enter the number of element:";
    cin>>n;

    int arr[n];

    cout<<"enter the element:";
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }

    parallel_bubble_sort(arr,n);

    cout<<"result:";
    for(int i = 0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }

}