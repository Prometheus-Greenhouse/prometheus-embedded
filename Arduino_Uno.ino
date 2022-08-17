#include<SoftwareSerial.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<DHT.h>
#define DHTPIN 4
DHT dht(DHTPIN,DHT11);
LiquidCrystal_I2C lcd(0X27,16,2);

#define WaterSensor 2
#define SensorIn A0
#define LED 8
#define R 13
#define G 12
#define B 11
char c;
String dataIn;
String res;
int light=0;


void setup() {
  Serial.begin(57600);
  Serial3.begin(57600);
  pinMode(WaterSensor,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  lcd.init();
  lcd.backlight();
  dht.begin();
}

int waterLevel()
{
  digitalWrite(WaterSensor,HIGH);
  delay(20);
  int value=analogRead(SensorIn);
  digitalWrite(WaterSensor,LOW);
  return value;
  }

  
void handleTopic()
  {
    int water=waterLevel();
    lcd.setCursor(2,0);
    lcd.print("Water Level:");
    lcd.setCursor(2,1);
    lcd.print(water);
    res="";
    res+=String(water)+"\n";
    Serial3.println(res);
  }

  
  void DHT11handle()
  {
    float h=dht.readHumidity();
    float t=dht.readTemperature();
    Serial.print("Humidity:");
    Serial.println(h);
    Serial.print("Temperature:");
    Serial.println(t);
    res="";
    res+=String(h)+" "+String(t)+" \n";
  }


void RGB(int r,int g,int b)
{
  analogWrite(R,r);
  analogWrite(G,g);
  analogWrite(B,b);
}
  
  void lightHandle()
  {
   light=analogRead(A1);
   if(light<100)
   {
    res+=("Very bright");
    RGB(255,0,0);
   }
   else if(light<200)
   {
    res+=("Bright");
    RGB(0,0,255);
   }
   else if(light<500)
   {
    res+=("Light");
    RGB(60,179,113);
   }
   else if(light<800)
   {
    res+=("Dim");
    RGB(255,165,0);
   }
   else
   {
    res+=("Dark");
    RGB(106,90,205);
   }
   res+="\n";
   Serial.println(res);
  }

  
void loop() {
while(Serial3.available()>0)
{ 
  c=Serial3.read();
  if(c=='\n')
  {
    break;
  }
  else
  {
    dataIn+=c;
  }
}
if(c=='\n')
{

if(dataIn=="sensor/1")
{
  lightHandle();
  delay(2000);
}
else if(dataIn=="sensor/2")
{
  handleTopic();
  delay(2000);
}
   c=0;
   dataIn="";
}
RGB(0,0,255);
}
