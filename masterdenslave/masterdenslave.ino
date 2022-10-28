#include <Wire.h> // Wire kütüphanemizi projemize dahil ediyoruz

String  endChar = String(char(0xff)) + String(char(0xff)) + String(char(0xff));

int deger=255;
int state="0";
int buzzer=7; 
byte alinan[2]; // Alınan veriyi hafızada tutmak için 2 indisli dizemiz 
byte alinan1[2];
byte alinan2[2];
byte akim[2];
byte hiz[2];


void setup() {
 
  Wire.begin(); // Wire haberleşmeyi Master olarak başlat
  Serial.begin(9600); // Seri haberleşmeyi 9600 baud rate ile başlat
  Serial2.begin(9600);
  
}
 
void loop() {
  
  Wire.requestFrom(1,2); // 1 numaralı slave cihaza 2 byte okuma isteği gönder.Sıcaklık verisini okur.
  
  if(Wire.available()){ // eğer gelen veri var ise
    int gelen = Wire.available();// Gelen byte sayısını gelen değişkenine aktar
    for(int i = 0; i<gelen; i++){ // gelen byte sayısı kadar döngüyü devam ettir
      alinan[i] = Wire.read(); // her döngüde 1 byte oku ve alinan dizisine aktar
    }
    word sonuc = word(alinan[0], alinan[1]); // okunan 2 byte veriyi bir word veriye dönüştür
    Serial.print("Sicaklik : ");  // Seri porta Okunan yaz aynı satırdan devam et
    Serial.println(sonuc); // sonucu seri porta yaz
    delay(1000); // 1 saniye bekle

      if(sonuc>60){ //gelen veri 60'dan büyükse
    Serial.print("kirmizi=");Serial.print(9); 
    Serial.print("uyari=");Serial.print(8); 
    digitalWrite(buzzer,HIGH);
    Serial.print("MOTOR SICAKLIGI KRiTiK");
  }
 
  else{ //değilse
    digitalWrite(buzzer,LOW);
    Serial.print("            ");
  }
  delay(100);

    Serial2.print("Max.val="); //nextion ekran motor sıcaklığı progress bar kodları
    Serial2.write(0x22); 
    Serial2.println(sonuc);
    Serial2.write(0x22);
    //Serial2.write(0xff);
    //Serial2.write(0xff);
    //Serial2.write(0xff);
  } 
  
  Wire.requestFrom(2,2); // 1 numaralı slave cihaza 2 byte okuma isteği gönder.Şarj verisini okur.
  
  if(Wire.available()){ // eğer gelen veri var ise
    int gelen1 = Wire.available();// Gelen byte sayısını gelen değişkenine aktar
    for(int i = 0; i<gelen1; i++){ // gelen byte sayısı kadar döngüyü devam ettir
      alinan1[i] = Wire.read(); // her döngüde 1 byte oku ve alinan dizisine aktar
    }
    word sonuc1 = word(alinan1[0], alinan1[1]); // okunan 2 byte veriyi bir word veriye dönüştür
    Serial.print("Şarj Yüzdesi : ");  // Seri porta Okunan yaz aynı satırdan devam et
    Serial.println(sonuc1); //şarj değerini seri porta yazdır.
    delay(1000); // 1 saniye bekle
    
    if(sonuc1<=20) {
    Serial.println("Sarj Seviyesi Az");
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(10);
     }

    Serial2.print("Full.val="); //nextion ekran şarj progress bar kodları
    Serial2.write(0x22);
    Serial2.println(sonuc1); 
    Serial2.write(0x22);
    //Serial2.write(0xff);
    //Serial2.write(0xff);
    //Serial2.write(0xff);
  } 
 
 /*Wire.requestFrom(3,2); // 1 numaralı slave cihaza 2 byte okuma isteği gönder.Pil sıcaklık verisini okur.
  
  if(Wire.available()){ // eğer gelen veri var ise
    int gelen2 = Wire.available();// Gelen byte sayısını gelen değişkenine aktar
    for(int i = 0; i<gelen2; i++){ // gelen byte sayısı kadar döngüyü devam ettir
      alinan[i] = Wire.read(); // her döngüde 1 byte oku ve alinan dizisine aktar
    }
    word sonuc2 = word(alinan[0], alinan[1]); // okunan 2 byte veriyi bir word veriye dönüştür
    Serial.print("Sicaklik : ");  // Seri porta Okunan yaz aynı satırdan devam et
    Serial.println(sonuc2); // sonucu seri porta yaz
    delay(1000); // 1 saniye bekle

      if(sonuc2>60){ //gelen veri 60'dan büyükse
    digitalWrite(buzzer,HIGH);
    Serial.print("PİL SICAKLIGI KRiTiK");
  }
  else{ //değilse
    digitalWrite(buzzer,LOW);
    Serial.print("            ");
  }
  delay(100);

    Serial2.print("t5.txt="); //nextion ekran batarya sıcaklığı text kodları
    Serial2.write(0x22);
    Serial2.println(sonuc2);
    Serial2.write(0x22);
    Wire.beginTransmission(6); // 6 numaralı aktarma başlat
    Wire.write(sonuc2); // Cihaza sonuc4 metnini gönder
    Wire.endTransmission(); // Altarmayı tamamla
    delay(1000);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
  }*/
  
  Wire.requestFrom(4,2); // 1 numaralı slave cihaza 2 byte okuma isteği gönder.Pil akım / gerilim okur.
  
  if(Wire.available()){ // eğer gelen veri var ise
    int gelen3 = Wire.available();// Gelen byte sayısını gelen değişkenine aktar
    for(int i = 0; i<gelen3; i++){ // gelen byte sayısı kadar döngüyü devam ettir
      akim[i] = Wire.read(); // her döngüde 1 byte oku ve alinan dizisine aktar
    }
    word sonuc3=word(akim[0],akim[1]);
    Serial.print("Bataryadan geçen akım= " );
    Serial.println(sonuc3); //akım değerini seri porta yazdır.
    delay(1000);

    Serial2.print("t1.txt="); //nextion ekran batarya akım text kodları
    Serial2.write(0x22);
    Serial2.println(sonuc3);
    Serial2.write(0x22);
   // Serial2.write(0xff); 
   //Serial2.write(0xff);
  // Serial2.write(0xff);
  }

  Wire.requestFrom(5,2); // 1 numaralı slave cihaza 2 byte okuma isteği gönder.Hız verisini okur.
  
  if(Wire.available()){ // eğer gelen veri var ise;
  int gelen4 =Wire.available(); // Gelen byte sayısını gelen değişkenine aktar.
  for(int i=0; i<gelen4; i++){ // gelen byte sayısı kadar döngüyü devam ettir.
      hiz[i] = Wire.read(); // her döngüde 1 byte oku ve alinan dizisine aktar.
}
  word sonuc4=word(hiz[0], hiz[1]);
  Serial.print("Arac Hizi km/h : ");
  Serial.println(sonuc4); //hız değerini seri porta yazdır.
  delay(1000); // 1 sn bekle

    Serial2.print("z0.val="); //nextion ekran gauge çubuğu kodları
    Serial2.write(0x22);
    Serial2.println(sonuc4);
    Serial2.write(0x22);
   // Serial2.write(0xff);
   // Serial2.write(0xff);
   // Serial2.write(0xff);
   
    
  delay(100);
//  sinyal();
  }
  temperature();
  delay(1000);
}
void temperature(){
  Wire.begin(3);
   Wire.onReceive(veriOku);
  
}
void veriOku(){
  if(Wire.available()){ // Eğer gelen veri varsa
    int gel =  Wire.available();
    for(int i=0; i<gel;i++){
      alinan[i]=Wire.read();
      }
      word sonuc2 = word(alinan[0], alinan[1]); // okunan 2 byte veriyi bir word veriye dönüştür
    Serial.print("Sicaklik : ");  // Seri porta Okunan yaz aynı satırdan devam et
    Serial.println(sonuc2);
    Serial2.print("t5.txt="); //nextion ekran batarya sıcaklığı text kodları
    Serial2.write(0x22);
    Serial2.println(sonuc2);
    Serial2.write(0x22);
    Wire.beginTransmission(6); // 6 numaralı aktarma başlat
    Wire.write(sonuc2); // Cihaza sonuc4 metnini gönder
    Wire.endTransmission(); // Altarmayı tamamla
    delay(1000);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
}
}
