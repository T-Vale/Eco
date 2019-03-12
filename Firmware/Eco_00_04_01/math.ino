int math_expo(int base, int coef)
{
  int result = base;
  if (coef == 0)
  {
    result = 1;
  }
  else
  {
    for (int x = 1; x < coef; x++)
    {
      result = result * base;
    }
  }
  return result;
}


