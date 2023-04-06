#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

char ssid[] = "HienNhien";
char pass[] = "31081978";

#define DHTPIN D0
#define MoiSens A0
#define LightSens D1
#define LED D2
#define PUMB D3
#define tempPin V1
#define humiPin V2
#define Auto D5

DHT dht(DHTPIN, DHT11);


void setup()
{
  // Debug console
  Serial.begin(9600);
  dht.begin();
  Blynk.begin("8vu6UvcvXdlQpc1YF1WOXoKSWvMZCiHP", ssid, pass,"iot.serangkota.go.id",8080);

  pinMode(MoiSens,INPUT);
  pinMode(LightSens, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(PUMB, OUTPUT);
  pinMode(Auto,INPUT);

}

void loop()
{
  Blynk.run();
  
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float _moist = map(analogRead(MoiSens),0,1024,0,100);
  bool _auto = digitalRead(Auto);
  bool _light = digitalRead(LightSens);

  
  
  Blynk.virtualWrite(tempPin,temperature);
  Blynk.virtualWrite(humiPin,humidity);

  if(_auto){
    if(_moist<=20){
      pumb(3);
    }

    if(!_light){
      digitalWrite(LED,HIGH);
    } else{
      digitalWrite(LED, LOW);
    }
  }else{
    Blynk.notify("HEY!");
  }
  

  delay(500);
}


void pumb(int t){
  digitalWrite(PUMB,HIGH);
  delay(t*1000);
}