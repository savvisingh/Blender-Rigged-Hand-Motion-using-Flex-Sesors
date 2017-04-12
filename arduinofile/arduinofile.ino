 #include <Servo.h>  //Servo library
 
 int ResThumb   = A0;  // Variables of the analog read form the flex sensors connected to the analog pins of Arduino LilyPad
int ResIndex   = A1;  
int ResMiddle  = A2;
int ResAnnular = A3;
int ResPinky   = A4;

int OpenedThumb   =0; // Variables of the values when the hand is completely opened
int OpenedIndex   =0; // This is needed for a continuous calibration
int OpenedMiddle  =0;
int OpenedAnnular =0;
int OpenedPinky   =0;

int ClosedThumb;      // Variables of the values when the hand is completely closed
int ClosedIndex;      // We can't set it to zero since that the minimum value reached
int ClosedMiddle;     // in the analog read never reach zero. We'll assign the value of
int ClosedAnnular;    // a first analog read, then the program in the loop will
int ClosedPinky;      // automatically  assing lower values

int thumb   =0;       // Variables of the values to send
int index   =0;
int middle  =0;
int annular =0;
int pinky   =0;
 
void setup() {
  // put your setup code here, to run once:

  // Turn the Serial Protocol ON
  Serial.begin(115200);
  Serial.flush(); 

  pinMode(ResThumb,   INPUT);   // The variables of the sensor are set as input
  pinMode(ResIndex,   INPUT);
  pinMode(ResMiddle,  INPUT);
  pinMode(ResAnnular, INPUT);
  pinMode(ResPinky,   INPUT);

  ClosedThumb   = analogRead(ResThumb);
  ClosedIndex   = analogRead(ResIndex);  
  ClosedMiddle  = analogRead(ResMiddle); 
  ClosedAnnular = analogRead(ResAnnular);
  ClosedPinky   = analogRead(ResPinky); 

}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
    if(Serial.read()=='a'){
      thumb   = analogRead(ResThumb);  
        index   = analogRead(ResIndex);  
        middle  = analogRead(ResMiddle); 
        annular = analogRead(ResAnnular);
        pinky   = analogRead(ResPinky);  
        
        if(thumb   > OpenedThumb)   // Calibration reading and setting the maximum values. This needs you to completely open your hand a few times
        OpenedThumb   = thumb;
        if(index   > OpenedIndex)
        OpenedIndex   = index;
        if(middle  >  OpenedMiddle)
        OpenedMiddle  = middle;
        if(annular > OpenedAnnular)
        OpenedAnnular = annular;
        if(pinky   > OpenedPinky)
        OpenedPinky   = pinky;
        
        if(thumb   < ClosedThumb)  // Calibration reading and setting the minimum values. This needs you to completely close your hand a few times
        ClosedThumb   = thumb;
        if(index   < ClosedIndex)
        ClosedIndex   = index;
        if(middle  < ClosedMiddle)
        ClosedMiddle  = middle;
        if(annular < ClosedAnnular)
        ClosedAnnular = annular;
        if(pinky   < ClosedPinky)
        ClosedPinky   = pinky;
        
        thumb   = map(thumb  ,OpenedThumb,ClosedThumb,   5200, 12000);  // The analog read has to be readapted in values between 0 and 180 to be used by the servomotors.
        index   = map(index  ,OpenedIndex  ,ClosedIndex  , 5200, 12000);  // The minimum and maximum values from the calibrations are used to correctly set the analog reads.
        middle  = map(middle ,OpenedMiddle , ClosedMiddle , 5200, 12000);
        annular = map(annular, OpenedAnnular, ClosedAnnular, 5200, 12000);  
        pinky   = map(pinky  ,OpenedPinky , ClosedPinky  , 5200, 12000);
        
        // This character represent the beginning of the package of the five values
        Serial.print(thumb);    // The values are sent via the Tx pin (the digital pin 1)
        Serial.print(",");
        Serial.print(index); 
        Serial.print(","); 
        Serial.print(middle);
        Serial.print(",");  
        Serial.print(annular);
        Serial.print(",");
        Serial.print(pinky);
        Serial.println("");
    }
  }
  delay(10);
}
