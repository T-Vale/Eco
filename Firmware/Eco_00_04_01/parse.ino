boolean parse_parameterReader(String receivedString, String parameterName, String &parameterStringValue, String breakChar)
{
  parameterStringValue = ""; //protege de repeticoes
  if (receivedString.indexOf(parameterName) >= 0)
  {
    for (int x = (receivedString.indexOf(parameterName) + parameterName.length()); x < receivedString.indexOf(breakChar, receivedString.indexOf(parameterName) + parameterName.length()); x++)
    {
      parameterStringValue += receivedString[x];
    }
    return true;
  }
  else
  {
    return false;
  }
}

int parse_dataBreaker(String dataString, String dataArray[], char breakChar, int maximumNumberOfFields)
{
  int breakCounter = 0;
  int dataStringLength = dataString.length();
  int n = 0;
  int previousBreak = 0;
  int arrayPosition = 0;

  while (n < dataStringLength)
  {
    if (dataString[n] == breakChar || n == dataStringLength - 1)
    {
      if (arrayPosition < maximumNumberOfFields)
      {
        if (dataString[n] == breakChar)
        {
          dataArray[arrayPosition] = dataString.substring(previousBreak, n);
        }
        else if (n == dataStringLength - 1)
        {
          dataArray[arrayPosition] = dataString.substring(previousBreak, n + 1);
        }
        arrayPosition++;
        previousBreak = n + 1; //para comecar a seguir
        breakCounter++;
      }
    }
    n++;
  }
  return arrayPosition; //assim da o numero de campos usados no vector
}

void parse_adcValueFinder(String receivedString, String &receivedStringValue, int adcWanted)
{
  int loc = 0;
  int x = 0;
  receivedStringValue = "";

  while(x <= adcWanted)
  {  
    loc = receivedString.indexOf("\t", loc + 1);
    x++;
  }
  if(x!= MAXIMUMNUMBEROFADCS)
  {
    receivedStringValue = receivedString.substring(loc + 1, receivedString.indexOf("\t", loc + 1));
  }
  else
  {
    receivedStringValue = receivedString.substring(loc + 1, receivedString.indexOf(newLine, loc + 1));
  }
}

