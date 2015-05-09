#include <RFM69.h>    //get it here: https://www.github.com/lowpowerlab/rfm69
#include <SPI.h>
#include <LowPower.h> //get library from: https://github.com/lowpowerlab/lowpower
#include <ECOCommons.h>

#define NODEID        2    //unique for each node on same network
#define NETWORKID     100  //the same on all nodes that talk to each other
#define GATEWAYID     1
#define FREQUENCY   RF69_868MHZ
#define IS_RFM69HW    //uncomment only for RFM69HW! Leave out if you have RFM69W!
#define LED           9 // Moteinos have LEDs on D9
#define FLASH_SS      8 // and FLASH SS on D8
#define SERIAL_BAUD   115200

//#define SERIAL_EN                //comment out if you don't want any serial output

#ifdef SERIAL_EN
  #define DEBUG(input)   {Serial.print(input); delay(1);}
  #define DEBUGln(input) {Serial.println(input); delay(1);}
#else
  #define DEBUG(input);
  #define DEBUGln(input);
#endif


char payload[] = "123 ABCDEFGHIJKLMNOPQRSTUVWXYZ";
RFM69 radio;
char buff[50];

void setup() {
#ifdef SERIAL_EN
  Serial.begin(SERIAL_BAUD);
#endif
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
#ifdef IS_RFM69HW
  radio.setHighPower(); //uncomment only for RFM69HW!
#endif
  radio.encrypt(ENCRYPTKEY);
  radio.sleep();
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  DEBUGln(buff);
  
  uint8_t devID;
  
  
  
}  
void loop() {  
 float temp = 0, rh = 0;
  //uint8_t status;

 
 
 //sprintf(buff, "TH|T:%s|H:%s", str_temp , str_rh);    
 byte sendSize = strlen(buff);
 DEBUG("Sending[");
 DEBUG(sendSize);
 DEBUG("]: ");
 DEBUG(buff);
 if (radio.sendWithRetry(GATEWAYID, buff, sendSize)) {
   DEBUGln(" ok!");
 }else {
   DEBUGln(" nothing...");
 }
 radio.sleep();
 Blink(LED,3);
 
 // On attend 10 min
 for (byte i = 0; i < 70; i++)
   LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}