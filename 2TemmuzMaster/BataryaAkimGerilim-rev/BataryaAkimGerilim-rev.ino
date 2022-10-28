#include <LiquidCrystal.h>
#include <Wire.h>

// LCD AYARLARI
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int analogIn = 0; //ACS712 SENSOR BAĞLANTI PINI
int mVperAmp = 66; // 185 5A MODÜL İÇİN , 100 20A MODÜL İÇİN VE 66  30A MODÜL İÇİN
int RawDeger = 0;
int ACSoffset = 2500;
int Voltage = 0; //VOLT HESABI
int Amps = 0;// AMPER HESABI

void setup() {
// LCD AYARI
Wire.begin(5);
Serial.begin(9600);
Wire.onRequest(olculen);
lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("ACS 712");
lcd.setCursor(0, 1);
lcd.print("  AKIM OLCUM  ");
delay(2000);
}

void loop(){
  delay(100);
  olculen();
}

void olculen() {
RawDeger = analogRead(analogIn);//MODUL ANALOG DEĞERI OKUNUYOR
word Voltage = (RawDeger / 1024.0) * 5000; // VOLT HESABI YAPILIYOR
word Amps = ((Voltage - ACSoffset) / mVperAmp); // AKIM HESAPLA

lcd.clear();
delay(1000);
lcd.display();
Wire.beginTransmission(5);
byte olculen[]={highByte(Voltage),lowByte(Voltage)};
//byte okunan[]={highByte(Amps),lowByte(Amps)};
//bu durumda sadece voltage değerini gönderiyor.
Wire.write(olculen,2);
Wire.endTransmission();

// VOLTAJI EKRANA YAZ
lcd.setCursor(1, 0);
lcd.print("Voltaj : ");
lcd.setCursor(8, 0);
lcd.print(Voltage, 3);
lcd.setCursor(12, 0);
lcd.print("mV");

// AKIMI EKRANA YAZ
lcd.setCursor(1, 1);
lcd.print("AMPER : ");
lcd.setCursor(7, 2);
lcd.print(Amps, 3);
lcd.setCursor(11, 2);
lcd.print("A");
delay(1000);


}
