//Fibonacci Series using Recursion
#include<stdio.h>

//recursive function
int fib(int n)
{
   if (n <= 1)
      return n;
   return fib(n-1) + fib(n-2);
}
 
//main function
int main ()
{
  int n = 10;
  printf("%d", fib(n));
  getchar();
  return 0;
}