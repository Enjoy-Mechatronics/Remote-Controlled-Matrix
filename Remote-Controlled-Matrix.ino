#include <LedControl.h>
#include <IRremote.h>

IRrecv recv(3);                 //IR Receiver Object

int DIN = 12;
int CS = 11;
int CLK = 10;
LedControl lc(DIN, CLK, CS, 1); //8x8 LED Matrix Object

//Facial Expressions
byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};
byte sad[8]=   {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};

int currentImage = 0;
int numberOfImages = 3;

void setup() {
 // put your setup code here
  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);

  recv.enableIRIn();
  
  Serial.begin(9600);
  drawImage(smile);
}
void loop() {
  // put your main code here
  if(recv.decode()){
    Serial.println(recv.decodedIRData.decodedRawData, HEX);
    //Check for next button
    if(recv.decodedIRData.decodedRawData == 0xBF40FF00){
      currentImage = currentImage +1;
      if(currentImage == numberOfImages){
        currentImage = 0;
      }
    }
    //Check for previous button
    if(recv.decodedIRData.decodedRawData == 0xBB44FF00){
      currentImage = currentImage -1;
      if(currentImage == -1){
        currentImage =numberOfImages -1;
      }
    }

    //Display the selected image using an index
    if(currentImage == 0){
      drawImage(smile);
    }else if(currentImage ==1){
      drawImage(neutral);
    }else if (currentImage ==2){
      drawImage(sad);
    }
    
    delay(1500);
    recv.resume();
  }

}

void drawImage(byte image[]){
  for(int i =0; i<=7; i++){
    lc.setRow(0, i, image[i]);
  }
}
