/////////////BMP280
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp;

float sonyukseklik=0, ilkyukseklik=0;

/////////////MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
/////////////BMP280
    Serial.begin(9600);
      while ( !Serial ) 
      delay(100);  
      unsigned status;
      status = bmp.begin(0x76);
          if (!status) {
                        Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "));
                        Serial.print("SensorID was: 0x"); 
                        Serial.println(bmp.sensorID(),16);
                        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
                        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
                        Serial.print("        ID of 0x60 represents a BME 280.\n");
                        Serial.print("        ID of 0x61 represents a BME 680.\n");
                        while (1) delay(10);
                        }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

                  ilkyukseklik=bmp.readAltitude(1013.25);

/////////////MPU6050
  if (!mpu.begin()) {
                       Serial.println("Failed to find MPU6050 chip");
                       while (1) {
                       delay(10);
                                 }
                     }

 mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
 mpu.setGyroRange(MPU6050_RANGE_500_DEG);
 mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(10);

}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

sonyukseklik=bmp.readAltitude(1013.25);
sonyukseklik=sonyukseklik-ilkyukseklik;

Serial.print("YUKSEKLIK = ");
Serial.println(sonyukseklik);
Serial.print("IVME X = ");
Serial.println(a.acceleration.x);
//Serial.print(bmp.readTemperature());Serial.print(a.acceleration.x);Serial.print(a.acceleration.y);Serial.print(a.acceleration.z);Serial.print(g.gyro.x);Serial.print(g.gyro.y);Serial.print(g.gyro.z);Serial.print(temp.temperature);

if(sonyukseklik>0.32 && a.acceleration.x>8)
{
  Serial.println("SURUKLENME PARASUTU ACİLDİ!!");
}
delay(500);

}
