#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


RF24 verici(9,8); //CE CSN

int deger;
int derece;
int hizDeger;
int paket[2];

const int kanal = 112;
void setup() 
{
  verici.begin();

  //set the address
  verici.openWritingPipe(kanal);

  //Set module as transmitter
  verici.stopListening();
  
}

void loop() 
{
  deger =analogRead(A0);
  derece = map(deger, 0,1023,140,90);
  hizDeger = analogRead(A2);
  paket[0] = derece;
  paket[1] = hizDeger;
  verici.write(&paket, sizeof(paket));
  //  delay(10);
}
