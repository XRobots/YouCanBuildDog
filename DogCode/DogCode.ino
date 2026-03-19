// James Bruton's Mini Dogs

#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int sw1;
int sw2;
int sw3;
int sw4;
int sw5;
int sw6;

int mode = 0;
int programCount = 0;

int playbackCount = 0;

int motion1 = 0;
int motion2 = 0;
int motion3 = 0;
int motion4 = 0;
int motion5 = 0;
int motion6 = 0;
int motion7 = 0;
int motion8 = 0;

float servo1Pos;
float servo1PosFiltered;
float servo2Pos;
float servo2PosFiltered;
float servo3Pos;
float servo3PosFiltered;
float servo4Pos;
float servo4PosFiltered;
float servo5Pos;
float servo5PosFiltered;
float servo6Pos;
float servo6PosFiltered;

int servo1Offset;
int servo2Offset;
int servo3Offset;
int servo4Offset;
int servo5Offset;
int servo6Offset;

unsigned long currentMillis;
long previousMillis = 0;        // set up timers
long previousPlaybackMillis = 0;        // set up timers
long previousWalkMillis = 0;        // set up timers

int stepTime = 200;
int filterVal = 5;

int walkAction = 0;        // triggers- for each motion
int walkCount = 0;   // counter for each stage of the walk

int inMotionFlag = 0;

void setup() {

  Serial.begin(115200);
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  servo1.attach(2);     // front left leg
  servo2.attach(3);     // back right leg
  servo3.attach(4);     // front right leg
  servo4.attach(5);     // back left leg
  servo5.attach(6);     // slider
  servo6.attach(7);     // rotation

  servo1Pos = 1800;
  servo2Pos = 1200;
  servo3Pos = 1800;
  servo4Pos = 1200;
  servo5Pos = 1500;
  servo6Pos = 1500;
  servo1PosFiltered = servo1Pos;
  servo2PosFiltered = servo2Pos;
  servo3PosFiltered = servo3Pos;
  servo4PosFiltered = servo4Pos;
  servo5PosFiltered = servo5Pos;
  servo6PosFiltered = servo6Pos; 


  // set all to zero to begin with, then fine tune servo rest postions
  servo1Offset = 0;         // front left leg
  servo2Offset = 0;         // back right leg
  servo3Offset = 0;         // back left leg
  servo4Offset = 0;         // front right leg
  servo5Offset = 0;      // slider
  servo6Offset = 100;       // rotation

  servo1.writeMicroseconds(1800);   // lower value picks up leg
  servo2.writeMicroseconds(1200);   // higher value picks up leg
  servo3.writeMicroseconds(1800);   // lower value picks up leg
  servo4.writeMicroseconds(1200);   // higher value picks up leg
  servo5.writeMicroseconds(1500);   // slider
  servo6.writeMicroseconds(1500);   // rotation
}

void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis >= 10) {  // start timed event    
      previousMillis = currentMillis;

      sw1 = digitalRead(A0); 
      sw2 = digitalRead(A1);
      sw3 = digitalRead(A2);
      sw4 = digitalRead(A3);
      sw5 = digitalRead(A4);   // start program / playback
      sw6 = digitalRead(A5);   // reset
      
      // *** toggle modes ***
      if (sw5 == 0 && mode == 0) {       // put into programming mode
        mode = 1; 
        digitalWrite(8, HIGH);           // status LED - start of programming
        digitalWrite(9, LOW);           // status LED
        digitalWrite(10, LOW);           // status LED
      }
      else if (sw6 == 0) {               // reset program
        mode = 0;
        digitalWrite(8, LOW);           // status LED
        digitalWrite(9, LOW);           // status LED
        digitalWrite(10, LOW);           // status LED
        programCount = 0;
        playbackCount = 0;
        motion1 = 0;
        motion2 = 0;
        motion3 = 0;
        motion4 = 0;
        motion5 = 0;
        motion6 = 0;
        motion7 = 0;
        motion8 = 0;
      }

      // *** start of programming ***
      if (mode == 1) {
        if (programCount == 0) {            // MOTION 1
          if (sw1 == 0) {
            motion1 = 1;
          }
          else if (sw2 == 0) {
            motion1 = 2;
          }
          else if (sw3 == 0) {
            motion1 = 3;
          }
          else if (sw4 == 0) {
            motion1 = 4;
          }
          else if (motion1 != 0) {
            Serial.print("motion1 is: ");
            Serial.println(motion1);
            programCount = 1;
          }          
        }
        else if (programCount == 1) {       // MOTION 2
          
          if (sw1 == 0) {
            motion2 = 1;
          }
          else if (sw2 == 0) {
            motion2 = 2;
          }
          else if (sw3 == 0) {
            motion2 = 3;
          }
          else if (sw4 == 0) {
            motion2 = 4;
          }
          else if (motion2 != 0) {
            Serial.print("motion2 is: ");
            Serial.println(motion2);
            programCount = 2;
          }
        }
        else if (programCount == 2) {       // MOTION 3
          if (sw1 == 0) {
            motion3 = 1;
          }
          else if (sw2 == 0) {
            motion3 = 2;
          }
          else if (sw3 == 0) {
            motion3 = 3;
          }
          else if (sw4 == 0) {
            motion3 = 4;
          }
          else if (motion3 != 0) {
            Serial.print("motion3 is: ");
            Serial.println(motion3);
            programCount = 3;
          }
        }
        else if (programCount == 3) {       // MOTION 4          
          if (sw1 == 0) {
            motion4 = 1;
          }
          else if (sw2 == 0) {
            motion4 = 2;
          }
          else if (sw3 == 0) {
            motion4 = 3;
          }
          else if (sw4 == 0) {
            motion4 = 4;
          }
          else if (motion4 != 0) {
            Serial.print("motion4 is: ");
            Serial.println(motion4);
            programCount = 4;
          }
        }
        else if (programCount == 4) {       // MOTION 5
          if (sw1 == 0) {
            motion5 = 1;
          }
          else if (sw2 == 0) {
            motion5 = 2;
          }
          else if (sw3 == 0) {
            motion5 = 3;
          }
          else if (sw4 == 0) {
            motion5 = 4;
          }
          else if (motion5 != 0) {
            Serial.print("motion5 is: ");
            Serial.println(motion5);
            programCount = 5;
          }
        }
        else if (programCount == 5) {       // MOTION 6  
          if (sw1 == 0) {
            motion6 = 1;
          }
          else if (sw2 == 0) {
            motion6 = 2;
          }
          else if (sw3 == 0) {
            motion6 = 3;
          }
          else if (sw4 == 0) {
            motion6 = 4;
          }
          else if (motion6 != 0) {
            Serial.print("motion6 is: ");
            Serial.println(motion6);
            programCount = 6;
          }
        }
        else if (programCount == 6) {       // MOTION 7          
          if (sw1 == 0) {
            motion7 = 1;
          }
          else if (sw2 == 0) {
            motion7 = 2;
          }
          else if (sw3 == 0) {
            motion7 = 3;
          }
          else if (sw4 == 0) {
            motion7 = 4;
          }
          else if (motion7 != 0) {
            Serial.print("motion7 is: ");
            Serial.println(motion7);
            programCount = 7;
          }
        }
        else if (programCount == 7) {       // MOTION 8          
          if (sw1 == 0) {
            motion8 = 1;
          }
          else if (sw2 == 0) {
            motion8 = 2;
          }
          else if (sw3 == 0) {
            motion8 = 3;
          }
          else if (sw4 == 0) {
            motion8 = 4;
          }
          else if (motion8 != 0) {
            Serial.print("motion8 is: ");
            Serial.println(motion8);
            programCount = 8;
            digitalWrite(8, LOW);           // status LED
            digitalWrite(9, HIGH);           // status LED - end of program
            digitalWrite(10, LOW);           // status LED
          }
        }

      } // end of programming

      // *** PLAYBACK ***

      if (programCount == 8 && sw5 == 0) {   // put into playback mode
        playbackCount = 0;
        mode = 2;
        digitalWrite(8, LOW);           // status LED
        digitalWrite(9, LOW);           // status LED
        digitalWrite(10, HIGH);         // status LED  - start of playback
        previousPlaybackMillis = currentMillis ;           
      }

      if (mode == 2) {                      // start playback              

        if (currentMillis - previousPlaybackMillis >= 500 && playbackCount == 0 && inMotionFlag == 0) {   
            previousPlaybackMillis = currentMillis;
            playbackCount = 1;
            walkCount = 0;
            walkAction = motion1;
            Serial.print("motion1 is "); 
            Serial.println(motion1);      
        }
        else if (currentMillis - previousPlaybackMillis >= 500 && playbackCount == 1 && inMotionFlag == 0) {    
            previousPlaybackMillis = currentMillis;
            playbackCount = 2; 
            walkCount = 0;
            walkAction = motion2;
            Serial.print("motion2 is "); 
            Serial.println(motion2);      
        }
        else if (currentMillis - previousPlaybackMillis >= 500 && playbackCount == 2 && inMotionFlag == 0) {    
            previousPlaybackMillis = currentMillis;
            playbackCount = 3;
            walkCount = 0;
            walkAction = motion3;
            Serial.print("motion3 is ");
            Serial.println(motion3);        
        }
        else if (currentMillis - previousPlaybackMillis >= 500 && playbackCount == 3 && inMotionFlag == 0) {   
            previousPlaybackMillis = currentMillis;
            playbackCount = 4;
            walkCount = 0;
            walkAction = motion4;
            Serial.print("motion4 is ");  
            Serial.println(motion4);      
        }
        else if (currentMillis - previousPlaybackMillis >= 500 && playbackCount == 4 && inMotionFlag == 0) {    
            previousPlaybackMillis = currentMillis;
            playbackCount = 5; 
            walkCount = 0;
            walkAction = motion5;
            Serial.print("motion5 is ");
            Serial.println(motion5);       
        }
        else if (currentMillis - previousPlaybackMillis >= 500 && playbackCount == 5 && inMotionFlag == 0) {    
            previousPlaybackMillis = currentMillis;
            playbackCount = 6;
            walkCount = 0;
            walkAction = motion6;
            Serial.print("motion6 is "); 
            Serial.println(motion6);       
        }
        else if (currentMillis - previousPlaybackMillis >= 500 && playbackCount == 6 && inMotionFlag == 0) {    
            previousPlaybackMillis = currentMillis;
            playbackCount = 7;
            walkCount = 0;
            walkAction = motion7;
            Serial.print("motion7 is ");  
            Serial.println(motion7);      
        }
        else if (currentMillis - previousPlaybackMillis >= 500 && playbackCount == 7 && inMotionFlag == 0) {    
            previousPlaybackMillis = currentMillis;
            playbackCount = 8; 
            walkCount = 0;
            walkAction = motion8;
            Serial.print("motion8 is "); 
            Serial.println(motion8);      
        }
        else if (currentMillis - previousPlaybackMillis >= 500 && playbackCount == 8 && inMotionFlag == 0) {   
            previousPlaybackMillis = currentMillis;
            playbackCount = 9;        
        }
        
      }   // end of playback

      // *** walking sequences ***

      // *** WALK FORWARD ***

      if (walkAction == 1) {      // walk forward sequence
        inMotionFlag = 1;         // *** in motion
        if (walkCount == 0) {
          // pick up FR and BL leg
          servo1Pos = 1000;
          servo2Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 1;
        }
        else if (walkCount == 1 && currentMillis - previousWalkMillis >= stepTime) {
          // slide
          servo5Pos = 1000;
          previousWalkMillis = currentMillis;
          walkCount = 2;
        }
        else if (walkCount == 2 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FR and BL leg
          servo1Pos = 1800;
          servo2Pos = 1200;
          previousWalkMillis = currentMillis;
          walkCount = 3;
        }
        else if (walkCount == 3 && currentMillis - previousWalkMillis >= stepTime) {
          // pick up FL and BR leg
          servo3Pos = 1000;
          servo4Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 4;
        }
        else if (walkCount == 4 && currentMillis - previousWalkMillis >= stepTime) {
          // slide
          servo5Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 5;
        }
        else if (walkCount == 5 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FL and BR leg
          servo3Pos = 1800;
          servo4Pos = 1200;
          previousWalkMillis = currentMillis;
          walkCount = 6;
        }
        else if (walkCount == 6 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FL and BR leg
          previousWalkMillis = currentMillis;
          inMotionFlag = 0;   // *** not in motion
        }     
      }  // *** END OF WALK FORWARD ***

      // *** WALK BACKWARD ***

      if (walkAction == 2) {      // walk backward sequence
        inMotionFlag = 1;         // *** in motion
        if (walkCount == 0) {
          // pick up FR and BL leg
          servo1Pos = 1000;
          servo2Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 1;
        }
        else if (walkCount == 1 && currentMillis - previousWalkMillis >= stepTime) {
          // slide
          servo5Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 2;
        }
        else if (walkCount == 2 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FR and BL leg
          servo1Pos = 1800;
          servo2Pos = 1200;
          previousWalkMillis = currentMillis;
          walkCount = 3;
        }
        else if (walkCount == 3 && currentMillis - previousWalkMillis >= stepTime) {
          // pick up FL and BR leg
          servo3Pos = 1000;
          servo4Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 4;
        }
        else if (walkCount == 4 && currentMillis - previousWalkMillis >= stepTime) {
          // slide
          servo5Pos = 1000;
          previousWalkMillis = currentMillis;
          walkCount = 5;
        }
        else if (walkCount == 5 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FL and BR leg
          servo3Pos = 1800;
          servo4Pos = 1200;
          previousWalkMillis = currentMillis;
          walkCount = 6;
        }
        else if (walkCount == 6 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FL and BR leg
          previousWalkMillis = currentMillis;
          inMotionFlag = 0;   // *** not in motion
        }     
      }  // *** END OF WALK BACKWARD ***

      // *** TURN LEFT ***

      if (walkAction == 3) {      // turn left sequence
        inMotionFlag = 1;         // *** in motion
        if (walkCount == 0) {
          // pick up FR and BL leg
          servo1Pos = 1000;
          servo2Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 1;
        }
        else if (walkCount == 1 && currentMillis - previousWalkMillis >= stepTime) {
          // slide
          servo5Pos = 1500;      // move slider to the middle
          servo6Pos = 800;      // rotate
          previousWalkMillis = currentMillis;
          walkCount = 2;
        }
        else if (walkCount == 2 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FR and BL leg
          servo1Pos = 1800;
          servo2Pos = 1200;
          previousWalkMillis = currentMillis;
          walkCount = 3;
        }
        else if (walkCount == 3 && currentMillis - previousWalkMillis >= stepTime) {
          // pick up FL and BR leg
          servo3Pos = 1000;
          servo4Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 4;
        }
        else if (walkCount == 4 && currentMillis - previousWalkMillis >= stepTime) {
          // slide
          servo6Pos = 1500;     // rotate back again
          previousWalkMillis = currentMillis;
          walkCount = 5;
        }
        else if (walkCount == 5 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FL and BR leg
          servo3Pos = 1800;
          servo4Pos = 1200;
          previousWalkMillis = currentMillis;
          walkCount = 6;
        }
        else if (walkCount == 6 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FL and BR leg
          previousWalkMillis = currentMillis;
          inMotionFlag = 0;   // *** not in motion
        }     
      }  // *** END OF TURN LEFT ***

      // *** TURN RIGHT ***

      if (walkAction == 4) {      // turn right sequence
        inMotionFlag = 1;         // *** in motion
        if (walkCount == 0) {
          // pick up FL and BR leg
          servo3Pos = 1000;
          servo4Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 1;
        }
        else if (walkCount == 1 && currentMillis - previousWalkMillis >= stepTime) {
          // slide
          servo5Pos = 1500;      // move slider to the middle
          servo6Pos = 800;      // rotate
          previousWalkMillis = currentMillis;
          walkCount = 2;
        }
        else if (walkCount == 2 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FL and BR leg
          servo3Pos = 1800;
          servo4Pos = 1200;
          previousWalkMillis = currentMillis;
          walkCount = 3;
        }
        else if (walkCount == 3 && currentMillis - previousWalkMillis >= stepTime) {
          // pick up FR and BL leg
          servo1Pos = 1000;
          servo2Pos = 2000;
          previousWalkMillis = currentMillis;
          walkCount = 4;
        }
        else if (walkCount == 4 && currentMillis - previousWalkMillis >= stepTime) {
          // slide
          servo6Pos = 1500;     // rotate back again
          previousWalkMillis = currentMillis;
          walkCount = 5;
        }
        else if (walkCount == 5 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FR and BL leg
          servo1Pos = 1800;
          servo2Pos = 1200;
          previousWalkMillis = currentMillis;
          walkCount = 6;
        }
        else if (walkCount == 6 && currentMillis - previousWalkMillis >= stepTime) {
          // put down FL and BR leg
          previousWalkMillis = currentMillis;
          inMotionFlag = 0;   // *** not in motion
        }     
      }  // *** END OF TURN RIGHT ***

      servo1PosFiltered = filter(servo1Pos, servo1PosFiltered, filterVal);
      servo2PosFiltered = filter(servo2Pos, servo2PosFiltered, filterVal);
      servo3PosFiltered = filter(servo3Pos, servo3PosFiltered, filterVal);
      servo4PosFiltered = filter(servo4Pos, servo4PosFiltered, filterVal);
      servo5PosFiltered = filter(servo5Pos, servo5PosFiltered, filterVal);
      servo6PosFiltered = filter(servo6Pos, servo6PosFiltered, filterVal);

      servo1.writeMicroseconds(servo1PosFiltered + servo1Offset);   // lower value picks up leg
      servo2.writeMicroseconds(servo2PosFiltered + servo2Offset);   // higher value picks up leg
      servo3.writeMicroseconds(servo3PosFiltered + servo3Offset);   // lower value picks up leg
      servo4.writeMicroseconds(servo4PosFiltered + servo4Offset);   // higher value picks up leg
      servo5.writeMicroseconds(servo5PosFiltered + servo5Offset);   // slider
      servo6.writeMicroseconds(servo6PosFiltered + servo6Offset);   // rotation            
      
    
  } // end of timed loop  


}

// motion filter to filter motions

float filter(float prevValue, float currentValue, int filter) {  
  float lengthFiltered =  (prevValue + (currentValue * filter)) / (filter + 1);  
  return lengthFiltered;  
}
