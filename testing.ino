#include <Adafruit_FRAM_SPI.h>
#include <SPI.h>


struct settings_t {
  int localTimeZone=5;
  bool localDST=true;
  bool localDisplayFormat24=true;
  int secondTimeZone=0;
  bool secondDST=false;
  bool secondDisplayFormat24=false;
  int brightness=4;
  bool autoBrightness=false;
} settings;
const int FRAM_CS = 5;
Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  fram.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  //int
  //if (fram.read(0, settings, (int)sizeof(settings))) Serial.println("worked");

  settings.localTimeZone = 5;
  settings.localDST = false;
  settings.localDisplayFormat24 = true;
  settings.secondTimeZone = 0;
  settings.secondDST = true;
  settings.secondDisplayFormat24 = true;
  settings.brightness = 6;
  settings.autoBrightness = False;
  Serial.println("Settings before writing");
  Serial.print(settings.localTimeZone);Serial.print(" - ");
  Serial.print(settings.localDST);Serial.print(" - ");
  Serial.print(settings.localDisplayFormat24);Serial.print(" - ");
  Serial.print(settings.secondTimeZone);Serial.print(" - ");
  Serial.print(settings.secondDST);Serial.print(" - ");
  Serial.print(settings.secondDisplayFormat24);Serial.print(" - ");
  Serial.print(setting.brightness);Serial.print(" - ");
  Serial.println(settings.autoBrightness);
  char buff[sizeof(settings)];
  memcpy(buff, &settings, sizeof(settings));
  Serial.println("Byte form of Array to be written");
  //write function
  for (uint16_t i = 0;i < sizeof(settings);i++){
    Serial.print(buff[i]);
    fram.writeEnable(true);
    fram.write8(i,buff[i]);
  }
  Serial.println("");
  Serial.println("Byte form of array as read");
  //read functin
  for (int16_t i = 0; i < sizeof(settings); i++){
    buff[i] = fram.read8[i];
    serial.print(buff[i]);
  }
  memcpy(&settings, buff, sizeof(settings));
  Serial.println("");
  Serial.println("Settings after write and read");
  Serial.print(settings.localTimeZone);Serial.print(" - ");
  Serial.print(settings.localDST);Serial.print(" - ");
  Serial.print(settings.localDisplayFormat24);Serial.print(" - ");
  Serial.print(settings.secondTimeZone);Serial.print(" - ");
  Serial.print(settings.secondDST);Serial.print(" - ");
  Serial.print(settings.secondDisplayFormat24);Serial.print(" - ");
  Serial.print(settings.brightness);Serial.print(" - ");
  Serial.println(settings.autoBrightness);
	delay(5000);
}

