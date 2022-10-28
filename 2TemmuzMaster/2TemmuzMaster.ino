#include <Wire.h> // Wire kütüphanemizi projemize dahil ediyoruz
 
byte alinan[2]; // Alınan veriyi hafızada tutmak için 2 indisli dizemiz 
byte alinan1[2];
byte alinan2[2];
void setup() {
  Wire.begin(); // Wire haberleşmeyi Master olarak başlat
  Serial.begin(9600); // Seri haberleşmeyi 9600 baud rate ile başlat
}
 
void loop() {
  Wire.requestFrom(1,2); // 1 numaralı slave cihaza 2 byte okuma isteği gönder.Sıcaklık verisini okur.
  
  if(Wire.available()){ // eğer gelen veri var ise
    int gelen = Wire.available();// Gelen byte sayısını gelen değişkenine aktar
    for(int i = 0; i<gelen; i++){ // gelen byte sayısı kadar döngüyü devam ettir
      alinan[i] = Wire.read(); // her döngüde 1 byte oku ve alinan dizisine aktar
    }
    word sonuc = word(alinan[0], alinan[1]); // okunan 2 byte veriyi bir word veriye dönüştür
    Serial.print("Okunan : ");  // Seri porta Okunan yaz aynı satırdan devam et
    Serial.println(sonuc); // sonucu seri porta yaz
    delay(1000); // 1 saniye bekle
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
  } 
  Wire.requestFrom(3,2); // 1 numaralı slave cihaza 2 byte okuma isteği gönder.Şarj verisini okur.
  
  if(Wire.available()){ // eğer gelen veri var ise
    int gelen2 = Wire.available();// Gelen byte sayısını gelen değişkenine aktar
    for(int i = 0; i<gelen2; i++){ // gelen byte sayısı kadar döngüyü devam ettir
      alinan2[i] = Wire.read(); // her döngüde 1 byte oku ve alinan dizisine aktar
    }
    word sonuc2 = word(alinan2[0], alinan2[1]); // okunan 2 byte veriyi bir word veriye dönüştür
    Serial.print("Şarj Yüzdesi : ");  // Seri porta Okunan yaz aynı satırdan devam et
    Serial.println(sonuc2); //şarj değerini seri porta yazdır.
    delay(1000); // 1 saniye bekle
  } 
}
