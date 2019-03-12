byte convert_Hexa(String valueString)
{
  int valueInt = 0;
  byte zero_Ascii = byte('0');
  byte nine_Ascii = byte('9');
  byte a_Ascii = byte('a');
  byte f_Ascii = byte('f');
  byte A_Ascii = byte('A');
  byte F_Ascii = byte('F');

  for (int g = 0; g < valueString.length(); g++)
  {
    byte valueStringAscii = byte(valueString[g]);
    int v = 0;
    if ((valueStringAscii >= zero_Ascii) && (valueStringAscii <= nine_Ascii))
    {
      v = valueStringAscii - zero_Ascii;
    }
    else if ((valueStringAscii >= a_Ascii) && (valueStringAscii <= f_Ascii))
    {
      v = valueStringAscii - a_Ascii + 10;
    }
    else if ((valueStringAscii >= A_Ascii) && (valueStringAscii <= F_Ascii))
    {
      v = valueStringAscii - A_Ascii + 10;
    }
    else
    {
      v = 0;
    }
    valueInt += v * math_expo(16, (valueString.length() - (g + 1)));
  }
  return valueInt;
}

void convert_addresses(String stringArray_[], byte byteArray_[], int numFields, int maxFields, int intOrHexa) //0 to int, 1 to hexa
{
  for (int a = 0; a < numFields; a++)
  {
    if (a < maxFields)
    {
      if (intOrHexa == 0)
      {
        byteArray_[a] = stringArray_[a].toInt();
      }
      else if (intOrHexa == 1)
      {
        byteArray_[a] = byte(convert_Hexa(stringArray_[a]));
      }
    }
  }
}


