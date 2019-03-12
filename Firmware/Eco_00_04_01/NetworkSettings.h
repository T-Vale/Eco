#define MAXIMUMNUMBEROFFIELDS 10
#define LINELENGTH 400

String myNameIs = "Eco";
String myFWIs = "00.04.01";

byte macAddress_[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0}; //colocar alguma coisa que diga que estas variaveis sao globais
byte ipAddress_ [4] = {0, 0, 0, 0};
byte gatewayAddress_[4] = {0, 0, 0, 0};
byte dnsAddress_[4] = {0, 0, 0, 0};

EthernetServer server(80);

int dataGraphArray_[5]; //0-ano 1-mes 2-dia 3-adc 4-tipo

