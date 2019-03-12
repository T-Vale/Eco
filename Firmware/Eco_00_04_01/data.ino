boolean data_write(String folder)
{
  time_t tempo = now();
  int annos = year(tempo);
  int mensis = month(tempo);
  int diems = day(tempo);
  int horas = hour(tempo);
  int minutes = minute(tempo);
  int seconds = second(tempo);


  read_value();

  String dataToWrite = String(annos) + "-" + String(mensis) + "-" + String(diems) + " " + String(horas) + ":" + String(minutes) + ":" + String(seconds) + "\t" +
                       String(adcValue_[0]) + "\t" + String(adcValue_[1]) + "\t" + String(adcValue_[2]) + "\t" + String(adcValue_[3]) + "\t" + String(adcValue_[4]) + "\t" + String(adcValue_[5]) + newLine;

  String fileLocation = "/" + folder + "/" + String(annos) + "/" + String(mensis);

  char charFileLocation[fileLocation.length() + 1]; //it only accepts character arrays
  fileLocation.toCharArray(charFileLocation, sizeof(charFileLocation));

  if (!SD.exists(charFileLocation))
  {
    if (!SD.mkdir(charFileLocation))
    {
      return false;
    }
  }
  fileLocation = fileLocation + "/" + String(diems) + ".TXT";

  if (!card_writeFile(fileLocation, dataToWrite))
  {
    return false;
  }

  return true;
}



