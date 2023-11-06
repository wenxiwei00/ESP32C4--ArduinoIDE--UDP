#include <WiFi.h>
#include <WiFiUdp.h>


const char* ssid = "618-5G"; //TP-Link_E0C8
const char* password = "618hhhhhh"; //52665134


IPAddress localIp(192, 168, 1, 201); //my esp32 IP 192.168.1.173
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


WiFiUDP udp;


const int localPort = 12345;
const char* remoteIp = "192.168.1.173"; //other people's esp32 IP 192, 168, 1, 201
const int UDPPort = 12345;


const int POT_PIN = 4;
const int LED_PIN = 8;


const int ledchannel = 0;
const int ledcresolution = 8;
const int ledcfreq = 3000;


void setup() {
  Serial.begin(115200);
  WiFi.config(localIp, gateway, subnet);  //my esp32 is station mode
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi with IP: ");
  Serial.println(WiFi.localIP());


  udp.begin(localPort);


  pinMode(POT_PIN, INPUT);
  ledcSetup(ledchannel, ledcfreq, ledcresolution);
  ledcAttachPin(LED_PIN, ledchannel);
}

void UdpSend(){
  // Read potentiometer value and send part
  int potValue = analogRead(POT_PIN);
  String potValueString = String(potValue); //send string. ex: from int 136 to string "136".end with /0. ex:136 /0
  udp.beginPacket(remoteIp, UDPPort);
  udp.write((const uint8_t*)potValueString.c_str(), potValueString.length()); //transform in C type string(end with null) 136
  udp.endPacket();
}

void UdpReceive(){
    // Check for incoming packets //receive part
  int packetSize = udp.parsePacket(); 
  if (packetSize) {   //if the length of the packet != 0, go into if
    char incomingPacket[255];   //set a array to hold the coming packet
    int len = udp.read(incomingPacket, 255); //get the length of the coming packet
    if (len > 0) {                //set the end string = 0 to let it know: it's end. 123\0，123 is the data we transform
      incomingPacket[len] = '\0';
    }
  int receivedValue = atoi(incomingPacket); //string to int
  int dutyCycle = map(receivedValue, 0, 4095, 0, 255); //potentiometer is 0--4095. resolution=8, led duty is 0-225

  ledcWrite(ledchannel, dutyCycle);

  }
}


void loop() {


  UdpSend();
  
  UdpReceive();

  delay(10);
}
