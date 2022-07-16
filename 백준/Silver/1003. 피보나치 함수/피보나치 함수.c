#include <stdio.h>

int T = 0, n = 0;
int fibonacci(int n);
int zero = 0, one = 0;

int arr[11] = {1,0,1,1,2,3,5,8,13,21,34};

int main(void) 
{
    int i;
    scanf("%d",&T);
    
    for(i=0;i<T;i++)
    {
        zero = 0;
        one = 0;
        
        scanf("%d",&n);
        fibonacci(n);
        printf("%d %d\n",zero, one);
    }
    return 0;
}

int fibonacci(int n) 
{
    if(n < 10)
    {
        zero += arr[n];
        one += arr[n+1];
        return 0;
    }
    else
    {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}