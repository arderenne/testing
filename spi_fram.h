#include <SPI.h>
 
const byte CMD_WREN = 0x06; //0000 0110 Set Write Enable Latch
const byte CMD_WRDI = 0x04; //0000 0100 Write Disable
const byte CMD_RDSR = 0x05; //0000 0101 Read Status Register
const byte CMD_WRSR = 0x01; //0000 0001 Write Status Register
const byte CMD_READ = 0x03; //0000 0011 Read Memory Data
const byte CMD_WRITE = 0x02; //0000 0010 Write Memory Data
 
const int FRAM_CS1 = 5; //chip select 1
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
/**
 * Write to FRAM (assuming 2 FM25C160 are used)
 * addr: starting address
 * buf: pointer to data
 * count: data length. 
 *        If this parameter is omitted, it is defaulted to one byte.
 * returns: 0 operation is successful
 *          1 address out of range
 */
void FRAMWrite(int addr, byte buf, int count)
{
  uint8_t* src;
  src = (uint8_t*)buf;
  digitalWrite(FRAM_CS1, LOW);   
  SPI.transfer(CMD_WREN);  //write enable 
  digitalWrite(FRAM_CS1, HIGH);
  digitalWrite(FRAM_CS1, LOW);   
  SPI.transfer((uint8_t)(addr >> 8));
  SPI.transfer((uint8_t)(addr & 0xFF));
  SPI.transfer(CMD_WRITE); //write command
  for (int i = 0;i < count;i++) SPI.transfer(*src++);
  digitalWrite(FRAM_CS1, HIGH);
  digitalWrite(FRAM_CS1, LOW);   
  SPI.transfer(CMD_WRDI);
  digitalWrite(FRAM_CS1, HIGH);
   
}
 
/**
 * Read frstartingom FRAM (assuming 2 FM25C160 are used)
 * addr:  address
 * buf: pointer to data
 * count: data length. 
 *        If this parameter is omitted, it is defaulted to one byte.
 * returns: 0 operation is successful
 *          1 address out of range
 */
void FRAMRead(int addr, byte buf, int count)
{
  uint8_t* dst;
  dst = (uint8_t*)buf;
  digitalWrite(FRAM_CS1, LOW);
  SPI.transfer(CMD_READ);
  SPI.transfer((uint8_t)(addr >> 8));
  SPI.transfer((uint8_t)(addr & 0xFF));
  for (int i=0; i < count; i++) *dst++ = SPI.transfer(0x00);
  digitalWrite(FRAM_CS1, HIGH);
   
}
 
