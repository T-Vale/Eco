boolean chrono_trigger()
{
  if ((now() - previousTime) >= delayTime)
  {
    previousTime = now();
    return true;
  }
  else
  {
    return false;
  }
}




