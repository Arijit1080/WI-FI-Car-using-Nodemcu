
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define InA1  D1
#define InB1  D2
#define InA2  D3
#define InB2  D4
#define pwm1  D5
#define pwm2  D6

int lspeed = 1024;
int rspeed = 1024;  


char auth[] = "fhF17gwMCymyO7Pt5Pudp0ruxieWQkrK";
char ssid[] = "Sparklers 2G";
char pass[] = "Awesome9883.";


void car_move(int x, int y)
{
//Move Forward
    if(y >= 750)
    {
          digitalWrite(InA1, HIGH); 
          digitalWrite(InA2, HIGH); 
          digitalWrite(InB1, LOW); 
          digitalWrite(InB2, LOW);
          analogWrite(pwm1,lspeed);
          analogWrite(pwm2,rspeed);
    }


//MoveRight
    else if(x >= 750)
    {
          digitalWrite(InA1, HIGH); 
          digitalWrite(InA2, LOW); 
          digitalWrite(InB1, LOW); 
          digitalWrite(InB2, HIGH);
          analogWrite(pwm1,lspeed);
          analogWrite(pwm2,rspeed);
    }

//Move Left
    else if(x <= 350)
    {
          digitalWrite(InA1, LOW); 
          digitalWrite(InA2, HIGH); 
          digitalWrite(InB1, HIGH); 
          digitalWrite(InB2, LOW);
          analogWrite(pwm1,lspeed);
          analogWrite(pwm2,rspeed);
    }

//No Move
    else if(x == 512 && y == 512)
    {
           digitalWrite(InA1, LOW); 
          digitalWrite(InA2, LOW); 
          digitalWrite(InB1, LOW); 
          digitalWrite(InB2, LOW);
    }

//Move Backward
    else if(y <= 350)
    {
        digitalWrite(InA1, LOW); 
          digitalWrite(InA2, LOW); 
          digitalWrite(InB1, HIGH); 
          digitalWrite(InB2, HIGH);
          analogWrite(pwm1,lspeed);
          analogWrite(pwm2,rspeed);
    }
}

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);

    pinMode(InA1, OUTPUT);
    pinMode(InB1 , OUTPUT);
    pinMode( InA2, OUTPUT);
    pinMode(InB2, OUTPUT);

    digitalWrite(InA1, LOW);
    digitalWrite(InA2 , LOW);
    digitalWrite(InB1, LOW);
    digitalWrite(InB2, LOW);

    pinMode(pwm1, OUTPUT);
    pinMode(pwm2, OUTPUT);
}


void loop()
{
    Blynk.run();
}


BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();
    car_move(x,y);
}
BLYNK_WRITE(V0){  
  lspeed = rspeed = param.asInt();
}
