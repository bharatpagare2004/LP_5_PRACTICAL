#include<iostream>
#include<omp.h>
using namespace std;

void merge(int arr[],int l,int m,int r)
{
    int n1 = m-l+1;
    int n2 = r-m;

    int L[n1];
    int R[n2];

    //for copy
    for(int i = 0;i<n1;i++)
     L[i] = arr[l+i];
    for(int j = 0;j<n2;j++)
    R[j] = arr[m+1+j];

    int i = 0;
    int j = 0;
    int k=l;

    while(i<n1&&j<n2)
    {
        if(L[i]<=R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i<n1)
     arr[k++] = L[i++];
    while(j<n2)
     arr[k++] = R[j++];

}

void parallel_merge_sort(int arr[],int l,int r)
{
    if(l<r)
    {
       int m = (r+l)/2;

       #pragma omp parallel sections
       {
        #pragma omp section
         parallel_merge_sort(arr,l,m);

         #pragma omp section
          parallel_merge_sort(arr,m+1,r);

       }

       merge(arr,l,m,r);
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

    parallel_merge_sort(arr,0,n-1);

    cout<<"result:";
    for(int i = 0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }

}