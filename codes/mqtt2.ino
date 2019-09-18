#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid="dipesh";
const char* password="dipesh9009";
const char* mqttServer="13.233.94.202";
const int mqttPort=1883;

WiFiClient esp;
PubSubClient node(esp);


#define LIGHT 4    //D2 on nodemcu
void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid,password);
  pinMode(LIGHT,OUTPUT);
  digitalWrite(LIGHT,LOW);


   while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.println("Connecting to WiFi............");
    delay(500);
  }
  Serial.println("Connected to Wifi!");
  node.setServer(mqttServer,mqttPort);
  node.setCallback(callback);
  while(!node.connected())
   {
   Serial.println("Connecting to MQTT.........");
   delay(500);
    if (node.connect("ESP8266Client")) {
      Serial.println("connected");  
      } 
      else {
      Serial.print("failed with state ");
      Serial.print(node.state());
      delay(2000);
    }
   }
   node.subscribe("light");
}


void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Recieved on topic: ");
  Serial.println(topic);
  Serial.println(length);
  for(int i=0;i<length;i++)
  Serial.print((char)payload[i]);
  Serial.println("payload[0]");
  Serial.println(payload[0]);
  Serial.println("payload[1]");
  Serial.println((char)payload[1]);
  Serial.println("payload[2]");
  Serial.println(payload[2]);
  Serial.println("");

//Checking condditions for devices and their status:

  if(((int)payload[0]==49) && ((int)payload[2]==52))
  {
    digitalWrite(LIGHT,HIGH);
    Serial.println("light turned on");
  } 
  else if(((int)payload[0]==48) && ((int)payload[2]==52))
  {
    digitalWrite(LIGHT,LOW);
    Serial.println("light turned off");
  }
  else if(((int)payload[0]==48) && ((int)payload[2]==53))
  {
    Serial.println("in else if party");
//    while(((int)payload[0]!=49))
for(int i=0;i<15;i++)
    {
//      if(payload[0]==49)
//      {
//        Serial.println("in break");
//        break;
//        
//      }
//      Serial.println(payload[0]);
      digitalWrite(LIGHT,HIGH);
      delay(200);
      digitalWrite(LIGHT,LOW);
      delay(200);
    }
  }
  if(((int)payload[0]==49) && ((int)payload[2]==54))
     {
       digitalWrite(LIGHT,LOW);
       Serial.println("sleep");
     }
}


void loop() {

  node.loop();
  // put your main code here, to run repeatedly:

}
