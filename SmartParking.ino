#include <Servo.h> //includes the servo library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels



// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 


#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8

Servo myservo;
int trig2=9; 
int echo2=10; 

int trig1=12; //trig pin of HC-SR04 is connected to pin 10 of Arduino
int echo1=11; //echo pin of HC-SR04 is connected to pin 9 of Arduino
int distance2;
int distance1;
int duration2;
int duration1;

int S1=0, S2=0, S3=0, S4=0; 
//int flag1=0, flag2=0; 
int slot = 4;  

void setup(){
 Serial.begin(9600);


  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);
pinMode(ir_car3, INPUT);
pinMode(ir_car4, INPUT);



pinMode(trig2,OUTPUT);  
pinMode(echo2,INPUT);
pinMode(trig1,OUTPUT);  
pinMode(echo1,INPUT);
myservo.attach(4); 


display.clearDisplay();
display.setTextSize(1.5);
display.setTextColor(WHITE);
display.setCursor(0, 10);
display.println("Car1 parking");
Read_Sensor();
int total = S1+S2+S3+S4;
slot = slot-total; 
}

void loop(){
Read_Sensor();
display.clearDisplay();
display.setTextSize(1.5);
display.setTextColor(WHITE);
display.setCursor(0, 10);
display.println("Car1 parking");
display.setCursor(0, 20);
if(S1==1){
  display.println("S1:Fill ");}
     else{display.println("S1:Empty");}
display.setCursor(0, 30);
if(S2==1){display.println("S2:Fill ");}
     else{display.println("S2:Empty");}
display.setCursor(0, 40);
if(S3==1){display.println("S3:Fill ");}
     else{display.println("S3:Empty");}

display.setCursor(0, 50);
if(S4==1){display.println("S4:Fill ");}
     else{display.println("S4:Empty");}
     display.display();
   

digitalWrite(trig2,LOW);   
delayMicroseconds(2000);
digitalWrite(trig2,HIGH);
delayMicroseconds(100);
digitalWrite(trig2,LOW);     
duration2=pulseIn(echo2,HIGH);  
distance2=duration2*0.034/2;
Serial.println(distance2);


digitalWrite(trig1,LOW);   
delayMicroseconds(2000);
digitalWrite(trig1,HIGH);
delayMicroseconds(100);
digitalWrite(trig1,LOW);     
duration1=pulseIn(echo1,HIGH);  
distance1=duration1*0.034/2;
Serial.println(distance1);
if(distance2>5 && distance2<14)
{
 // Read_Sensor();
  if(slot>0)
  {
    myservo.write(0);
    slot=slot-1;
    delay(3000);
  }
}
else if(distance1>5 && distance1<14)
{
  myservo.write(0);
  slot=slot+1;
  delay(3000);
}
myservo.write(90);
delay(100);

}
void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0;
if(digitalRead(ir_car1) == 0){S1=1;}
if(digitalRead(ir_car2) == 0){S2=1;}
if(digitalRead(ir_car3) == 0){S3=1;}
if(digitalRead(ir_car4) == 0){S4=1;}

}
