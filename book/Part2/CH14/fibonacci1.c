// CH14:fibonacci1.c
long int fib1(int n)
{
  if ((n == 1) || (n == 2)) // base case 
    { return 1; } 
  return (fib1(n - 1) + fib1(n - 2)); // recursive case 
}  
