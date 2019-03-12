boolean card_readFile(String fileName, String &fileContent, byte maxStringSize) //reads a specified file and fills the passed string until it reachs the maxStringSize or its end
{
  fileContent = "";
  File openedFile = SD.open(fileName, FILE_READ);
  if (!openedFile)
  {
    openedFile.close();
    return false;
  }
  byte cNumber = 0;
  while (openedFile.available() && cNumber < maxStringSize) //limits the size, protecting the memory used
  {
    char c = openedFile.read();
    fileContent = fileContent + c;
    cNumber++;
  }
  openedFile.flush();
  openedFile.close();
  return true;
}

boolean card_writeFile(String fileName, String dataContent)
{
  File dataFile = SD.open(fileName, FILE_WRITE);
  if (dataFile)
  {
    dataFile.print(dataContent);
    dataFile.close();
    return true;
  }
  else
  {
    dataFile.close();
    return false;
  }
}

byte card_readSensorLocation(String directoryName) //loads the sensor file names in an array and returns the number of sensors
{
  File directoryFile = SD.open(directoryName, FILE_READ);
  String buff;
  while (true && directoryFile.isDirectory() && (sensorNumber < MAXIMUMNUMBEROFSENSORS))
  {
    File entry = directoryFile.openNextFile();
    if (!entry)
    {
      entry.close();
      directoryFile.close();
      return sensorNumber;
    }
    else if (entry.isDirectory())
    {
      entry.close();
    }
    else
    {
      String fileName = entry.name();
      entry.close();
      fileName = "/" + directoryName + "/" + fileName;
      config_sensorVerifier(fileName);
    }
  }
}

boolean card_removeFile(String location)
{
  char charlocation[location.length() + 1]; //it only accepts character arrays
  location.toCharArray(charlocation, sizeof(charlocation));
  if (SD.remove(charlocation))
  {
    return true;
  }
  else
  {
    return false;
  }
}



