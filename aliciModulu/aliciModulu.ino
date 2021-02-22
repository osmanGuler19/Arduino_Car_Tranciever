#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;
SoftwareSerial hc06(3,10); //Rx Tx
RF24 alici(9,8); //CE CSN

int alinanPaket[2];

int joyposVert =512;
int hiz =0;

const int in4 =4;
const int in2 =2;
const int enb =5;

const int kanal = 112;
void setup() {
  servo.attach(6);    
  alici.begin();
  //set the address
  alici.openReadingPipe(0, kanal);
  //Set module as receiver
  alici.startListening();


  TCCR0B = TCCR0B & B11111000 | B00000001;
  pinMode(enb, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in2, OUTPUT);

  //Motor disabled and direction forward

  digitalWrite(enb, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in2, LOW);

  //Bluetooth part*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
  Serial.begin(9600);
  hc06.begin(9600);
}

void loop() {
  if (alici.available())
  {
    int derece;
    alici.read(&alinanPaket, sizeof(alinanPaket));
    servo.write(alinanPaket[0]);
    joyposVert = alinanPaket[1];
    
    if(joyposVert < 460)
    {
      //Motor backward
      digitalWrite(in4, LOW);
      digitalWrite(in2, HIGH);
  
      //Geri girederken hız değeri de tersten düşünülmeli
  
      joyposVert = joyposVert-460; //This produces negative number
      joyposVert = joyposVert * -1; // Make the number positive
  
      //Hız
      hiz = map(joyposVert, 0, 460, 0, 255);
    }
    else if(joyposVert > 564)
    {
      
      //Motor forward
      digitalWrite(in4, HIGH);
      digitalWrite(in2, LOW);
  
      //Hız 
  
      hiz = map(joyposVert, 564, 1023, 0, 255);
    }
    else
    {
      //Stopped
      hiz= 0;
    }
    analogWrite(enb,hiz);
  }

}
