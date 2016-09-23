#include <Adafruit_FRAM_SPI.h>


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
  fram.begin)_;
  //initSPI();
}
void initSPI(){
  pinMode(FRAM_CS1, OUTPUT);
  digitalWrite(FRAM_CS1, HIGH);
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);  
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  delay(5000);
}
void loop() {
  // put your main code here, to run repeatedly:
  //int
  //if (fram.read(0, settings, (int)sizeof(settings))) Serial.println("worked");
  settings.autoBrightness = true;
  char buff[sizeof(settings)];
  memcpy(buff, &settings, sizeof(settings));
  for (int i = 0;i < sizeof(settings);i++){
    Serial.print(buff[i]);
    
  }
  
  memcpy(&settings, buff, sizeof(settings));

  Serial.print(settings.localTimeZone);
  Serial.print(settings.localDST);
  Serial.print(settings.localDisplayFormat24);
  Serial.print(settings.secondTimeZone);
  Serial.print(settings.secondDST);
  Serial.print(settings.secondDisplayFormat24);
  Serial.print(settings.brightness);
  Serial.println(settings.autoBrightness);
	delay(5000);
}

