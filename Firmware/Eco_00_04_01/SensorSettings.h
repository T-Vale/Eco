#define MAXIMUMNUMBEROFADCS 6
#define MAXIMUMNUMBEROFSENSORS 20

#define MAXIMUMNUMBEROFCHARACTERS 200

float adcValue_[MAXIMUMNUMBEROFADCS];
int adcPinout_[MAXIMUMNUMBEROFADCS] = {A0, A1, A2, A3, A4, A5};
int adcSensor_[MAXIMUMNUMBEROFADCS] = { -1, -1, -1, -1, -1, -1};

int sensorNumber = 0;
String sensorLocation_[MAXIMUMNUMBEROFSENSORS];
String sensorName_[MAXIMUMNUMBEROFSENSORS];
String sensorType_[MAXIMUMNUMBEROFSENSORS];
String sensorUnit_[MAXIMUMNUMBEROFSENSORS];
int sensorEqGrade_[MAXIMUMNUMBEROFSENSORS];
float sensorEqM_[MAXIMUMNUMBEROFSENSORS];
float sensorEqB_[MAXIMUMNUMBEROFSENSORS];
float sensorGraphMin_[MAXIMUMNUMBEROFSENSORS];
float sensorGraphMax_[MAXIMUMNUMBEROFSENSORS];

int alarmOnOffPinout_[MAXIMUMNUMBEROFADCS] = {A6, A7, A8, A9, A10, A11};
int alarmSoundPinout_[MAXIMUMNUMBEROFADCS] = {A6, A7, A8, A9, A10, A11};

float alarmMin_[MAXIMUMNUMBEROFADCS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float alarmMax_[MAXIMUMNUMBEROFADCS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float alarmHys_[MAXIMUMNUMBEROFADCS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
boolean alarmStatus_[MAXIMUMNUMBEROFADCS] = {false, false, false, false, false, false};
boolean alarmOn_[MAXIMUMNUMBEROFADCS] = {false, false, false, false, false, false};

Adafruit_SHT31 sht31 = Adafruit_SHT31();
