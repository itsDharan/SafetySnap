#include <SoftwareSerial.h>
#include <TinyGPS++.h>

float lattitude, longitude; // Create variables for latitude and longitude
SoftwareSerial gpsSerial(8, 9); // GPS module TX to pin 8, RX to pin 9
SoftwareSerial gsmm(2, 3);      // GSM module TX to pin 2, RX to pin 3
TinyGPSPlus gps;                // Create GPS object

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  gpsSerial.listen();
  textgps();

  gsmm.begin(9600);
  gsmm.print("\r");
  delay(1000);
  gsmm.print("AT+CMGF=1\r"); // Set SMS mode
  delay(1000);

  /* Replace XXXXXXXXXX with a 10-digit mobile number & ZZ with a 2-digit country code */
  gsmm.print("AT+CMGS=\"+916201668754\"\r");
  delay(1000);

  // Send Google Maps URL
  gsmm.print("https://www.google.com/maps/place/");
  gsmm.print(lattitude, 6);
  gsmm.print(",");
  gsmm.print(longitude, 6);
  
  delay(1000);
  gsmm.write(0x1A); // End SMS
  delay(1000);
}

void loop() {
  // No actions in the loop
}

void textgps() {
  while (1) {
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }

    if (gps.location.isUpdated()) {
      Serial.print("LAT = ");  Serial.println(gps.location.lat(), 6);
      Serial.print("LONG = "); Serial.println(gps.location.lng(), 6);

      lattitude = gps.location.lat();
      longitude = gps.location.lng();
      break;
    }
  }

  Serial.print("LATTITUDE = "); Serial.println(lattitude, 6);
  Serial.print("LONGITUDE = "); Serial.println(longitude, 6);
  delay(1000);
}
