// CH14:fibonacci2.c
long int fib2(int n)
{
  if ((n == 1) || (n == 2))
    { return 1; }
  long int fna = 1; // fib(1) 
  long int fnb = 1; // fib(2) 
  long int fnc;     // to hold the latest value of fib
  while (n > 2)
    {
      fnc = fnb + fna; // the new value
      fna = fnb;
      fnb = fnc; 
      n --;
    }
  return fnc;
}
