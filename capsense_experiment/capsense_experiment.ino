#include  <MsTimer2.h>

#include  "i2cdevice.h"

void setup() {
  // put your setup code here, to run once:
  int err = 0;
  int i;

  //  Initialize Hardware
  wireBegin();
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  for (i=0; i<4; ++i){
    err += pca9544_changeI2cBus(i);
    err += MBR3110_setup(0);
  }
  if (err){
    while(1){}
  }
  digitalWrite(2, LOW);

  for (i=0; i<4; ++i){
    pca9544_changeI2cBus(i);
    err = MBR3110_init(0);
  }

  //  Set Interrupt
  MsTimer2::set(10, flash);     // 10ms Interval Timer Interrupt
  MsTimer2::start();
}

void loop() {

  uint8_t sw_bit[4][2] = {0};
  int err = 1;
  
  //  read sensor
  for (int i=0; i<4; ++i){
    pca9544_changeI2cBus(i);
    err = MBR3110_readTouchSw(sw_bit[i],0);
  }

  //  display
  int swon = 0;
  for (int j=0; j<4; j++){
    for ( int k=0; k<2; k++){
      swon += sw_bit[j][k];
    }
  }
  if ( swon ){
    digitalWrite(2, HIGH);
    delay(50);
    digitalWrite(2, LOW);
  }  
}

void flash()  // every 10msec
{

}
