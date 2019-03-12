boolean config_networkParameters(String nconfigFileName)  // !!!!!!! reads network parameters from the card and applies them
{
  String nconfigFileContent = "";
  String buff = "";

  byte numberOfFields;
  String arrayOfValues[MAXIMUMNUMBEROFFIELDS];

  boolean macRead = false;
  boolean ipRead = false;
  boolean gatewayRead = false;
  boolean dnsRead = false;

  if (card_readFile(nconfigFileName, nconfigFileContent, MAXIMUMNUMBEROFCHARACTERS))
  {
    if (parse_parameterReader(nconfigFileContent, "mac=", buff, serialEndChar)) //buff is always reset in the parse function
    {
      numberOfFields = parse_dataBreaker(buff, arrayOfValues, ':', MAXIMUMNUMBEROFFIELDS);
      convert_addresses(arrayOfValues, macAddress_, numberOfFields, 6, 1);
      macRead = true;
    }
    if (parse_parameterReader(nconfigFileContent, "ip=", buff, serialEndChar))
    {
      numberOfFields = parse_dataBreaker(buff, arrayOfValues, '.', MAXIMUMNUMBEROFFIELDS);
      convert_addresses(arrayOfValues, ipAddress_, numberOfFields, 4, 0);
      ipRead = true;
    }
    if (parse_parameterReader(nconfigFileContent, "dns=", buff, serialEndChar))
    {
      numberOfFields = parse_dataBreaker(buff, arrayOfValues, '.', MAXIMUMNUMBEROFFIELDS);
      convert_addresses(arrayOfValues, dnsAddress_, numberOfFields, 4, 0);
      dnsRead = true;
    }
    if (parse_parameterReader(nconfigFileContent, "gateway=", buff, serialEndChar))
    {
      numberOfFields = parse_dataBreaker(buff, arrayOfValues, '.', MAXIMUMNUMBEROFFIELDS);
      convert_addresses(arrayOfValues, gatewayAddress_, numberOfFields, 4, 0);
      gatewayRead = true;
    }
  }
  return macRead && ipRead && gatewayRead && dnsRead;
}

boolean config_sensorPrevAssigned(String location)
{
  String content = "";
  String buff = "";

  if (card_readFile(location, content, MAXIMUMNUMBEROFCHARACTERS))
  {
    for (byte i = 0; i < MAXIMUMNUMBEROFADCS; i++)
    {
      String adc = "ADC" + String(i) + ":";
      if (parse_parameterReader(content, adc, buff, serialEndChar))
      {
        for (int w = 0; w < sensorNumber; w++) //to check if the sensor is already listed
        {
          if (buff.equals(sensorLocation_[w]))
          {
            adcSensor_[i] = w;
          }
          /*else
          {
            if (config_sensorVerifier(buff))
            {
              adcSensor_[i] = sensorNumber - 1;
            }
          }*/
        }
      }
      else
      {
        card_removeFile(location);
        
        /*char charlocation[location.length() + 1]; //it only accepts character arrays
        location.toCharArray(charlocation, sizeof(charlocation));
        SD.remove(charlocation);*/
        
        delay(250);
        return false;
      }
    }
  }
  else
  {
    return false;
  }
  return true;
}

boolean config_sensorVerifier(String location)
{
  String content = "";
  if (card_readFile(location, content, MAXIMUMNUMBEROFCHARACTERS))
  {
    boolean isName = false;
    boolean isType = false;
    boolean isUnit = false;
    boolean isGrade = false;
    boolean isM = false;
    boolean isB = false;
    boolean isGraphMin = false;
    boolean isGraphMax = false;

    String Name = "";
    String Type = "";
    String Unit = "";
    int Grade = 0;
    float M = 0.00;
    float B = 0.00;
    float GraphMin = 0.00;
    float GraphMax = 0.00;

    String buff = "";

    if (parse_parameterReader(content, "name=", buff, serialEndChar)) //buff is always reset in the parse function
    {
      Name = buff;
      isName = true;
    }
    if (parse_parameterReader(content, "type=", buff, serialEndChar))
    {
      Type = buff;
      isType = true;
    }
    if (parse_parameterReader(content, "unit=", buff, serialEndChar))
    {
      Unit = buff;
      isUnit = true;
    }
    if (parse_parameterReader(content, "grade=", buff, serialEndChar))
    {
      Grade = buff.toInt();
      isGrade = true;
    }
    if (parse_parameterReader(content, "m=", buff, serialEndChar))
    {
      M = buff.toFloat();
      isM = true;
    }
    if (parse_parameterReader(content, "b=", buff, serialEndChar))
    {
      B = buff.toFloat();
      isB = true;
    }
    if (parse_parameterReader(content, "graphmin=", buff, serialEndChar))
    {
      GraphMin = buff.toFloat();
      isGraphMin = true;
    }
    if (parse_parameterReader(content, "graphmax=", buff, serialEndChar))
    {
      GraphMax = buff.toFloat();
      isGraphMax = true;
    }
    if (isName && isType && isUnit && isGrade && isM  && isB && isGraphMin && isGraphMax && (sensorNumber < MAXIMUMNUMBEROFSENSORS))
    {
      sensorLocation_[sensorNumber] = location;
      sensorName_[sensorNumber] = Name;
      sensorType_[sensorNumber] = Type;
      sensorUnit_[sensorNumber] = Unit;
      sensorEqGrade_[sensorNumber] = Grade;
      sensorEqM_[sensorNumber] = M;
      sensorEqB_[sensorNumber] = B;
      sensorGraphMin_[sensorNumber] = GraphMin;
      sensorGraphMax_[sensorNumber] = GraphMax;
      sensorNumber++;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

boolean config_delayParameters(String nconfigFileName)  // !!!!!!! reads delay values from the card and applies them
{
  String nconfigFileContent = "";
  String buff = "";

  boolean wdelayRead = false;
  int wdelayNum = 60;

  if (card_readFile(nconfigFileName, nconfigFileContent, MAXIMUMNUMBEROFCHARACTERS))
  {
    if (parse_parameterReader(nconfigFileContent, "wdelay=", buff, serialEndChar)) //buff is always reset in the parse function
    {
      wdelayNum = buff.toInt();
      wdelayRead = true;
    }
  }
  delayTime = wdelayNum;
  return wdelayRead;
}

boolean config_alarms(String location)
{
  String content = "";
  String buff = "";
  float numBuff = 0;
  String fileLocation = "/" + location + "/" + alarmsMinimumFileName;
  if (card_readFile(fileLocation, content, MAXIMUMNUMBEROFCHARACTERS))
  {
    for (byte i = 0; i < MAXIMUMNUMBEROFADCS; i++)
    {
      String adc = "ADC" + String(i) + ":";
      if (parse_parameterReader(content, adc, buff, serialEndChar))
      {
        numBuff = buff.toFloat();
        alarmMin_[i] = numBuff;
      }
      else
      {
        card_removeFile(location);
        delay(250);
        return false;
      }
    }
  }
  else
  {
    return false;
  }
  fileLocation = "/" + location + "/" + alarmsMaximumFileName;
  if (card_readFile(fileLocation, content, MAXIMUMNUMBEROFCHARACTERS))
  {
    for (byte i = 0; i < MAXIMUMNUMBEROFADCS; i++)
    {
      String adc = "ADC" + String(i) + ":";
      if (parse_parameterReader(content, adc, buff, serialEndChar))
      {
        numBuff = buff.toFloat();
        alarmMax_[i] = numBuff;
      }
      else
      {
        card_removeFile(location);
        delay(250);
        return false;
      }
    }
  }
  else
  {
    return false;
  }
  fileLocation = "/" + location + "/" + alarmsHysteresisFileName;
  if (card_readFile(fileLocation, content, MAXIMUMNUMBEROFCHARACTERS))
  {
    for (byte i = 0; i < MAXIMUMNUMBEROFADCS; i++)
    {
      String adc = "ADC" + String(i) + ":";
      if (parse_parameterReader(content, adc, buff, serialEndChar))
      {
        numBuff = buff.toFloat();
        alarmHys_[i] = numBuff;
      }
      else
      {
        card_removeFile(location);
        delay(250);
        return false;
      }
    }
  }
  else
  {
    return false;
  }
  fileLocation = "/" + location + "/" + alarmsStatusFileName;
  if (card_readFile(fileLocation, content, MAXIMUMNUMBEROFCHARACTERS))
  {
    for (byte i = 0; i < MAXIMUMNUMBEROFADCS; i++)
    {
      String adc = "ADC" + String(i) + ":";
      if (parse_parameterReader(content, adc, buff, serialEndChar))
      {
        numBuff = buff.toInt();
        if(numBuff == 1)
        {
          alarmStatus_[i] = true;
        }
        if(numBuff == 0)
        {
          alarmStatus_[i] = false;
        }
        else
        {
          card_removeFile(location);
        }
      }
      else
      {
        card_removeFile(location);
        delay(250);
        return false;
      }
    }
  }
  else
  {
    return false;
  }
  return true;
}



