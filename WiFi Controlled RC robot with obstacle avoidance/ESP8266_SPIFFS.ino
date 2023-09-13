
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include<Servo.h>

AsyncWebServer server(80);
Servo myServo;
int servpin=D8;
int m1en=D0;
int m1i1=D1;
int m1i2=D2;
int m2en=D3;
int m2i1=D4;
int m2i2=D5;
int ech=D7;
int pulse=D6;
int dt=10;
int ValRead;
int CM;
int dm;
int y;
char* ssid = "Hammads's Galaxy A32";
char* password = "12345678913";
void forward();
void sto();
void right();
void left();
void rev();
int distance();
int dir();

void setup()
{
  SPIFFS.begin();
  pinMode(m1en, OUTPUT);
  pinMode(m1i2, OUTPUT);
  pinMode(m1i1, OUTPUT);
  pinMode(m2en, OUTPUT);
  pinMode(m2i2, OUTPUT);
  pinMode(m2i1, OUTPUT);
  pinMode(pulse,OUTPUT);
  pinMode(ech,INPUT);
  myServo.attach(servpin);
 
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });
  
  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css", "text/css");
 
  });
    server.on("/F", HTTP_GET, [](AsyncWebServerRequest *request){
      forward();
 
  });
     server.on("/R", HTTP_GET, [](AsyncWebServerRequest *request){
      right();
 
  });
     server.on("/L", HTTP_GET, [](AsyncWebServerRequest *request){
      left();
 
  });
     server.on("/RE", HTTP_GET, [](AsyncWebServerRequest *request){
      rev();
 
  });
    server.on("/S", HTTP_GET, [](AsyncWebServerRequest *request){
      sto();
 
  });






  server.begin();
}

void loop()
{
  myServo.write(90);

  dm=distance();
  Serial.println(dm);


  
  if(dm<25){
  analogWrite(m1en,0);
  analogWrite(m2en,0);
  y=dir();
  Serial.println(y);
  switch(y)
  {
    case 1:
     right();
     delay(1000);
     sto();
     break;

     
    case 2:
     left();
     delay(1000);
     sto();
     break;

    case 3:
    left();
    delay(1600);
    sto();
    break;
    }
  }
  

}


void forward()
{ 
   digitalWrite(m1i1,HIGH);
   digitalWrite(m1i2,LOW);
   digitalWrite(m2i1,HIGH);
   digitalWrite(m2i2,LOW);
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });
  
  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css", "text/css");
  });

   analogWrite(m1en,180);
   analogWrite(m2en,120);
  }


void sto()
{ 
  digitalWrite(m1i1,HIGH);
  digitalWrite(m1i2,LOW);
  digitalWrite(m2i1,HIGH);
  digitalWrite(m2i2,LOW);
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });
  
  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css", "text/css");
  });
  analogWrite(m1en,0);
  analogWrite(m2en,0);

}


void right()
{  
  digitalWrite(m1i1,HIGH);
  digitalWrite(m1i2,LOW);
  digitalWrite(m2i1,HIGH);
  digitalWrite(m2i2,LOW);
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });
  
  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css", "text/css");
  });
  analogWrite(m1en,0);
  analogWrite(m2en,170);
 
}


void left()
{  
  digitalWrite(m1i1,HIGH);
  digitalWrite(m1i2,LOW);
  digitalWrite(m2i1,HIGH);
  digitalWrite(m2i2,LOW);
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });
  
  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css", "text/css");
  });
  analogWrite(m1en,200);
  analogWrite(m2en,0);

}


void rev()
{
  digitalWrite(m1i1,LOW);
  digitalWrite(m1i2,HIGH);
  digitalWrite(m2i1,LOW);
  digitalWrite(m2i2,HIGH);
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });
  
  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css", "text/css");
  });
  analogWrite(m1en,255);
  analogWrite(m2en,200);

  
}


int distance()
{
  digitalWrite(pulse,LOW);
  delayMicroseconds(dt);
  digitalWrite(pulse,HIGH);
  delayMicroseconds(dt);
  digitalWrite(pulse,LOW);
  ValRead=pulseIn(ech,HIGH);
  CM=34300.*(ValRead/1000000.);
  delay(10);
  return CM;
  }
int dir(){
  int x;
  int arr[2]={0,0};
  myServo.write(0);
  delay(500);
  arr[0]=distance();
  myServo.write(180);
  delay(500);
  arr[1]=distance();
  if(arr[0]>25){
      x=1;
    }
   else if (arr[1]>25){
      x=2;
    }
else if(arr[0]<25 && arr[1]<25){
      x=3;
    }
return x;
}

    
