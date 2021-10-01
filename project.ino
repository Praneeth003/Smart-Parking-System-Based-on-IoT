#include <WiFi.h>
#include <ThingSpeak.h>

//Name of WiFi Router
const char* ssid = "Praneeth";
//WiFi Password    
const char* password = "qwertyuiop";      
const char* host = "api.thingspeak.com";
//Write key of our channel   
const char* writekey = "CZXAUYYVA1TWIPES";  

int parking1_slot1 = 26;
int parking1_slot2 = 25;
int parking1_slot3 = 33;

int parking2_slot1 = 32;
int parking2_slot2 = 35;
int parking2_slot3 = 34;

int p1s1, p1s2, p1s3, p2s1, p2s2, p2s3;
String line;

void setup() {
  
  // put your setup code here, to run once:
  
  pinMode(parking1_slot1,INPUT);
  pinMode(parking1_slot2,INPUT);
  pinMode(parking1_slot3,INPUT);
  pinMode(parking2_slot1,INPUT);
  pinMode(parking2_slot2,INPUT);
  pinMode(parking2_slot3,INPUT);
  
  
  Serial.begin(115200);
  delay(3000);

  Serial.print("Connecting to "); 
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
  
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  // put your main code here, to run repeatedly:
  
  p1s1 = digitalRead(parking1_slot1);
  p1s2 = digitalRead(parking1_slot2);
  p1s3 = digitalRead(parking1_slot3);
  p2s1 = digitalRead(parking2_slot1);
  p2s2 = digitalRead(parking2_slot2);
  p2s3 = digitalRead(parking2_slot3);

  upload();
  delay(1000);
}

void upload()
{
  Serial.println("Connecting to:");
  Serial.println(host);
  Serial.println();

  // Making TCP Connections
  
  WiFiClient client;
  const int httpPort = 80;
  
  if(!client.connect(host,httpPort))
  {
    return;
  }
  String url = "/update";
  url += "?api_key=";
  url += writekey;  
  url += "&field1="; 
  url += p1s1;
  url += "&field2="; 
  url += p1s2;
  url += "&field3="; 
  url += p1s3;
  url += "&field4="; 
  url += p2s1;
  url += "&field5="; 
  url += p2s2;
  url += "&field6="; 
  url += p2s3;

  //Request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +"Connection: close\r\n\r\n");
  delay(3000);
  
  //Status of Parking Area 1
  if( p1s1==0 && p1s2==0 && p1s3==0 )
  {
    Serial.println("Parking Area 1 is FULL!! ");
  }
  else
  {
    Serial.println("Empty slots in Parking Area 1 are: ");
    if( p1s1==1 )
    {
      Serial.println("Slot 1 ");  
    }
    if( p1s2==1 )
    {
      Serial.println("Slot 2 ");  
    }
    if( p1s3==1 )
    {
      Serial.println("Slot 3 ");  
    }
  }

  // Status of Parking Area 2
  if( p2s1==0 && p2s2==0 && p2s3==0 )
  {
    Serial.println("Parking Area 2 is FULL!! ");
  }
  else
  {
    Serial.println("Empty slots in Parking Area 2 are: ");
    if( p2s1==1 )
    {
      Serial.println("Slot 1 ");  
    }
    if( p2s2==1 )
    {
      Serial.println("Slot 2 ");  
    }
    if( p2s3==1 )
    {
      Serial.println("Slot 3 ");  
    }}
    Serial.println("Closing Connection ");
    Serial.println();
}
 
  
 
   
  


  
  
  
