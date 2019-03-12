boolean htmlRequest_timeSetting(String receivedLine, String endChar)
{
  String strBuff = "";
  int numBuff;

  int annos;
  int mensis;
  int diems;
  int horas;
  int minutes;
  int seconds;
  int annosRead = false;
  int mensisRead = false;
  int diemsRead = false;
  int horasRead = false;
  int minutesRead = false;
  int secondsRead = false;

  if (parse_parameterReader(receivedLine, "year=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff > 1980 && numBuff <= 5000)
    {
      annosRead = true;
      annos = numBuff;
    }
    else
    {
      annosRead = false;
      //return false; //acelera o processo
    }
  }
  if (parse_parameterReader(receivedLine, "month=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff > 0 && numBuff <= 12)
    {
      mensisRead = true;
      mensis = numBuff;
    }
    else
    {
      mensisRead = false;
    }
  }
  if (parse_parameterReader(receivedLine, "day=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff > 0 && numBuff <= 31)
    {
      diemsRead = true;
      diems = numBuff;
    }
    else
    {
      diemsRead = false;
    }
  }
  if (parse_parameterReader(receivedLine, "hour=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff >= 0 && numBuff < 24)
    {
      horasRead = true;
      horas = numBuff;
    }
    else
    {
      horasRead = false;
    }
  }
  if (parse_parameterReader(receivedLine, "minute=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff >= 0 && numBuff < 60)
    {
      minutesRead = true;
      minutes = numBuff;
    }
    else
    {
      minutesRead = false;
    }
  }
  if (parse_parameterReader(receivedLine, "second=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff >= 0 && numBuff < 60)
    {
      secondsRead = true;
      seconds = numBuff;
    }
    else
    {
      secondsRead = false;
    }
  }
  if (annosRead && mensisRead && diemsRead && horasRead && minutesRead && secondsRead)
  {
    setTime(horas, minutes, seconds, diems, mensis, annos);
    RTC.set(now());
    previousTime = now() + delayTime; //saves data right after this
    return true;
  }
  else
  {
    return false;
  }
}

boolean htmlRequest_delaySetting(String receivedLine, String endChar)
{
  String strBuff = "";
  int numBuff;

  boolean delaysRead = false;
  int delays = 60;


  if (parse_parameterReader(receivedLine, "delay=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff >= 60 && numBuff <= 30000)
    {
      delaysRead = true;
      delays = numBuff;
    }
    else
    {
      delaysRead = false;
    }
  }
  if (delaysRead)
  {
    delayTime = delays;
    card_removeFile(delayConfigFileName);
    String toWrite = "wdelay=" + String(delayTime) + ";";
    card_writeFile(delayConfigFileName, toWrite);
    return true;
  }
  else
  {
    //delayTime = delays; //assim sempre que ha um POST o delay é actualizado para 60s
    return false;
  }
}

boolean htmlRequest_adcPost(String receivedLine, String endChar)
{
  String strBuff = "";
  int numBuff;

  boolean adcReadValidation = true;
  int adcSensorAssigned_[MAXIMUMNUMBEROFADCS];

  for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
  {
    if (parse_parameterReader(receivedLine, "adc" + String(adc) + "=", strBuff, endChar)) //buff is always reset in the parse function
    {
      numBuff = strBuff.toInt();
      if (numBuff >= -1 && numBuff < sensorNumber)
      {
        adcSensorAssigned_[adc] = numBuff;
      }
      else
      {
        adcReadValidation = false;
        break;
      }
    }
    else
    {
      adcReadValidation = false;
      break;
    }
  }

  if (adcReadValidation)
  {
    card_removeFile(assignedSensorsFileName);
    for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
    {
      adcSensor_[adc] = adcSensorAssigned_[adc];
      String toWrite = "ADC" + String(adc) + ":";
      if (adcSensor_[adc] != -1)
      {
        toWrite = toWrite + sensorLocation_[adcSensor_[adc]] + serialEndChar + newLine;
      }
      else
      {
        toWrite = toWrite + "na" + serialEndChar + newLine;
      }
      card_writeFile(assignedSensorsFileName, toWrite);
    }
    return true;
  }
  else
  {
    return false;
  }
}

boolean htmlRequest_plotGraph(String receivedLine, String endChar)
{
  String strBuff = "";
  int numBuff;

  int annos;
  int mensis;
  int diems;
  boolean annosRead = false;
  boolean mensisRead = false;
  boolean diemsRead = false;

  int adcChosen;
  int adcChosenRead = false;

  int type = -1;
  boolean typeRead = false;

  if (parse_parameterReader(receivedLine, "dyear=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff > 1980 && numBuff <= 5000)
    {
      annosRead = true;
      annos = numBuff;
    }
    else
    {
      annosRead = false;
    }
  }
  if (parse_parameterReader(receivedLine, "dmonth=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff > 0 && numBuff <= 12)
    {
      mensisRead = true;
      mensis = numBuff;
    }
    else
    {
      mensisRead = false;
    }
  }
  if (parse_parameterReader(receivedLine, "dday=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff > 0 && numBuff <= 31)
    {
      diemsRead = true;
      diems = numBuff;
    }
    else
    {
      diemsRead = false;
    }
  }
  if (parse_parameterReader(receivedLine, "dadc=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff >= 0 && numBuff < MAXIMUMNUMBEROFADCS && adcSensor_[numBuff] >= 0 && adcSensor_[numBuff] < MAXIMUMNUMBEROFSENSORS)
    {
      adcChosenRead = true;
      adcChosen = numBuff;
    }
    else
    {
      adcChosenRead = false;
    }
  }
  if (parse_parameterReader(receivedLine, "dtype=", strBuff, endChar)) //buff is always reset in the parse function
  {
    numBuff = strBuff.toInt();
    if (numBuff >= 0 && numBuff <= 1)
    {
      typeRead = true;
      type = numBuff;
    }
    else
    {
      typeRead = false;
    }
  }
  if (annosRead && mensisRead && diemsRead && adcChosenRead && typeRead)
  {
    dataGraphArray_[0] = annos;
    dataGraphArray_[1] = mensis;
    dataGraphArray_[2] = diems;
    dataGraphArray_[3] = adcChosen;
    dataGraphArray_[4] = type;
    return true;
  }
  else
  {
    return false;
  }
}

boolean htmlRequest_defineAlarms(String receivedLine, String endChar)
{
  String strBuff = "";
  int numBuff;

  boolean alarmReadValidation = true;

  for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
  {
    if (parse_parameterReader(receivedLine, "alarm" + String(adc) + "=", strBuff, endChar)) //buff is always reset in the parse function
    {
      numBuff = strBuff.toInt();
      if (numBuff == 1)
      {
        alarmStatus_[adc] = true;
      }
      else if (numBuff == 0)
      {
        alarmStatus_[adc] = false;
        alarm_activator(adc, false);
      }
      else
      {
        alarmReadValidation = false;
        break;
      }
    }
    else
    {
      alarmReadValidation = false;
      break;
    }
    if (parse_parameterReader(receivedLine, "alarmmax" + String(adc) + "=", strBuff, endChar)) //buff is always reset in the parse function
    {
      numBuff = strBuff.toFloat();
      alarmMax_[adc] = numBuff;
    }
    else
    {
      alarmReadValidation = false;
      break;
    }
    if (parse_parameterReader(receivedLine, "alarmmin" + String(adc) + "=", strBuff, endChar)) //buff is always reset in the parse function
    {
      numBuff = strBuff.toFloat();
      alarmMin_[adc] = numBuff;
    }
    else
    {
      alarmReadValidation = false;
      break;
    }
    if (parse_parameterReader(receivedLine, "alarmhys" + String(adc) + "=", strBuff, endChar)) //buff is always reset in the parse function
    {
      numBuff = strBuff.toFloat();
      alarmHys_[adc] = numBuff;
    }
    else
    {
      alarmReadValidation = false;
      break;
    }
  }

  if (alarmReadValidation)
  {
    card_removeFile("/" + alarmsFolder + "/" + alarmsMinimumFileName);
    card_removeFile("/" + alarmsFolder + "/" + alarmsMaximumFileName);
    card_removeFile("/" + alarmsFolder + "/" + alarmsHysteresisFileName);
    card_removeFile("/" + alarmsFolder + "/" + alarmsStatusFileName);
    
    for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
    {
      String toWrite = "ADC" + String(adc) + ":" + String(alarmMin_[adc]) + serialEndChar + newLine;
      card_writeFile("/" + alarmsFolder + "/" + alarmsMinimumFileName, toWrite);
      toWrite = "ADC" + String(adc) + ":" + String(alarmMax_[adc]) + serialEndChar + newLine;
      card_writeFile("/" + alarmsFolder + "/" + alarmsMaximumFileName, toWrite);
      toWrite = "ADC" + String(adc) + ":" + String(alarmHys_[adc]) + serialEndChar + newLine;
      card_writeFile("/" + alarmsFolder + "/" + alarmsHysteresisFileName, toWrite);
      if (alarmStatus_[adc])
      {
        toWrite = "ADC" + String(adc) + ":" + "1" + serialEndChar + newLine;
      }
      else
      {
        toWrite = "ADC" + String(adc) + ":" + "0" + serialEndChar + newLine;
      }
      card_writeFile("/" + alarmsFolder + "/" + alarmsStatusFileName, toWrite);
    }
    return true;
  }
  else
  {
    return false;
  }
}
