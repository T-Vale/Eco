void alarm_watchdog()
{ 
  float sensorValue = 0;
  read_value();
  
  for(int a = 0; a < MAXIMUMNUMBEROFADCS; a++)
  {
    if(adcSensor_[a] != -1 && alarmStatus_[a])
    {
      sensorValue = adcValue_[a] * sensorEqM_[adcSensor_[a]] + sensorEqB_[adcSensor_[a]];
      if((sensorValue > alarmMax_[a] || sensorValue < alarmMin_[a]) && !alarmOn_[a])
      {
        alarm_activator(a, true);
      }
      else if(alarmOn_[a] && ((sensorValue < alarmMax_[a] - alarmHys_[a]) && (sensorValue > alarmMin_[a] + alarmHys_[a])))
      {
        alarm_activator(a, false);
      }
    }
  }
}


void alarm_activator(int adc, boolean state)
{
  digitalWrite(alarmOnOffPinout_[adc], state);
  digitalWrite(alarmSoundPinout_[adc], state);
  alarmOn_[adc] = state;
}

