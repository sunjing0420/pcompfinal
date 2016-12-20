#include "pitches.h"

#include <Wire.h>
#include "Adafruit_MPR121.h"

Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int touching;
bool showing = false;

// notes in the melody:
int melody[] = {
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4
};

//4051
int r0 = 0;      //value of select pin at the 4051 (s0)
int r1 = 0;      //value of select pin at the 4051 (s1)
int r2 = 0;      //value of select pin at the 4051 (s2)
int count = 0;   //which y pin we are selecting

int s0Pin = 2;
int s1Pin = 3;
int s2Pin = 4;

int buzzerPin = 8;
int sound;

int part = 0;
int iCount = 0;
int lastPlayed = 0;
bool released = false;
int parts1[] = {0, 3, 3, 4, 3, 2, 1, 1};
int parts2[] = {1, 4, 4, 5, 4, 3, 2, 0};
int parts3[] = {0, 5, 5, 6, 5, 4, 3, 1};
int parts4[] = {0, 0, 1, 4, 2, 3};


//int lightPin[] = {5, 6, 9, 10, 11, 12, 13};
int lightPin[]={5,6,9,10,11};



void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  pinMode(buzzerPin, OUTPUT);

  pinMode(s0Pin, OUTPUT);    // s0
  pinMode(s1Pin, OUTPUT);    // s1
  pinMode(s2Pin, OUTPUT);    // s2

  for (int i = 0; i < 7; i++) {
    pinMode(lightPin[i], OUTPUT);
  }

  Serial.println("CAP1188 test!");

  

}

int playPart = 0;
int note = 0;


void loop() {
  if (part == 4) {
    for(int i=0;i<7;i++){
      digitalWrite(lightPin[i],LOW);
    }
    delay(1000);
    tone(buzzerPin, melody[parts1[0]], 600);
    digitalWrite(lightPin[0], HIGH);
    delay(680);
    digitalWrite(lightPin[0], LOW);
    tone(buzzerPin, melody[parts1[1]], 600);
    digitalWrite(lightPin[3], HIGH);
    delay(680);
    digitalWrite(lightPin[3], LOW);
    tone(buzzerPin, melody[parts1[2]], 260);
    digitalWrite(lightPin[3], HIGH);
    delay(300);
    tone(buzzerPin, melody[parts1[3]], 260);
    digitalWrite(lightPin[3], LOW);
    digitalWrite(lightPin[4], HIGH);
    delay(300);
    digitalWrite(lightPin[4], LOW);
    tone(buzzerPin, melody[parts1[4]], 260);
    digitalWrite(lightPin[3], HIGH);
    delay(300);
    digitalWrite(lightPin[3], LOW);
    tone(buzzerPin, melody[parts1[5]], 260);
    digitalWrite(lightPin[2], HIGH);
    delay(300);
    digitalWrite(lightPin[2], LOW);
    tone(buzzerPin, melody[parts1[6]], 600);
    digitalWrite(lightPin[1], HIGH);
    delay(680);
    digitalWrite(lightPin[1], LOW);
    tone(buzzerPin, melody[parts1[7]], 600);
    digitalWrite(lightPin[1], HIGH);
    delay(680);
    digitalWrite(lightPin[1], LOW);
    tone(buzzerPin, melody[parts2[0]], 600);
    digitalWrite(lightPin[1], HIGH);
    delay(680);
    digitalWrite(lightPin[1], LOW);
    tone(buzzerPin, melody[parts2[1]], 600);
    digitalWrite(lightPin[4], HIGH);
    delay(680);
    digitalWrite(lightPin[4], LOW);
    tone(buzzerPin, melody[parts2[2]], 260);
    digitalWrite(lightPin[4], HIGH);
    delay(300);
    digitalWrite(lightPin[4], LOW);
    tone(buzzerPin, melody[parts2[3]], 260);
    digitalWrite(lightPin[2], HIGH);
    digitalWrite(lightPin[0], HIGH);
    delay(300);
    digitalWrite(lightPin[2], LOW);
    digitalWrite(lightPin[0], LOW);
    tone(buzzerPin, melody[parts2[4]], 260);
    digitalWrite(lightPin[4], HIGH);
    delay(300);
    digitalWrite(lightPin[4], LOW);
    tone(buzzerPin, melody[parts2[5]], 260);
    digitalWrite(lightPin[3], HIGH);
    delay(300);
    digitalWrite(lightPin[3], LOW);
    tone(buzzerPin, melody[parts2[6]], 600);
    digitalWrite(lightPin[2], HIGH);
    delay(680);
    digitalWrite(lightPin[2], LOW);
    tone(buzzerPin, melody[parts2[7]], 600);
    digitalWrite(lightPin[0], HIGH);
    delay(680);
    digitalWrite(lightPin[0], LOW);
    tone(buzzerPin, melody[parts3[0]], 600);
    digitalWrite(lightPin[0], HIGH);
    digitalWrite(lightPin[1], HIGH);
    delay(680);
    digitalWrite(lightPin[0], LOW);
    digitalWrite(lightPin[1], LOW);
    tone(buzzerPin, melody[parts3[1]], 600);
    digitalWrite(lightPin[2], HIGH);
    delay(680);
    digitalWrite(lightPin[2], LOW);
    tone(buzzerPin, melody[parts3[2]], 260);
    digitalWrite(lightPin[4], HIGH);
    digitalWrite(lightPin[3], HIGH);
    delay(300);
    digitalWrite(lightPin[4], LOW);
    digitalWrite(lightPin[3], LOW);
    tone(buzzerPin, melody[parts3[3]], 260);
    digitalWrite(lightPin[0], HIGH);
    delay(300);
    digitalWrite(lightPin[0], LOW);
    tone(buzzerPin, melody[parts3[4]], 260);
    digitalWrite(lightPin[4], HIGH);
    digitalWrite(lightPin[2], HIGH);
    delay(300);
    digitalWrite(lightPin[4], LOW);
    digitalWrite(lightPin[2], LOW);
    tone(buzzerPin, melody[parts3[5]], 260);
    digitalWrite(lightPin[4], HIGH);
    delay(300);
    digitalWrite(lightPin[4], LOW);
    tone(buzzerPin, melody[parts3[6]], 600);
    digitalWrite(lightPin[3], HIGH);
    delay(680);
    digitalWrite(lightPin[3], LOW);
    tone(buzzerPin, melody[parts3[7]], 600);
    digitalWrite(lightPin[1], HIGH);
    delay(680);
    digitalWrite(lightPin[1], LOW);
    tone(buzzerPin, melody[parts4[0]], 260);
    digitalWrite(lightPin[0], HIGH);
    delay(300);
    digitalWrite(lightPin[0], LOW);
    tone(buzzerPin, melody[parts4[1]], 260);
    digitalWrite(lightPin[0], HIGH);
    delay(300);
    digitalWrite(lightPin[0], LOW);
    tone(buzzerPin, melody[parts4[2]], 600);
    digitalWrite(lightPin[1], HIGH);
    delay(680);
    digitalWrite(lightPin[1], LOW);
    tone(buzzerPin, melody[parts4[3]], 600);
    digitalWrite(lightPin[4], HIGH);
    delay(680);
    digitalWrite(lightPin[4], LOW);
    tone(buzzerPin, melody[parts4[4]], 550);
    digitalWrite(lightPin[2], HIGH);
    delay(590);
    digitalWrite(lightPin[2], LOW);
    tone(buzzerPin, melody[parts4[5]], 1000);
    digitalWrite(lightPin[3], HIGH);
    delay(1100);
    digitalWrite(lightPin[0], HIGH);
    digitalWrite(lightPin[1], HIGH);
    digitalWrite(lightPin[2], HIGH);
    digitalWrite(lightPin[3], HIGH);
    digitalWrite(lightPin[4], HIGH);
    digitalWrite(lightPin[5], HIGH);
    digitalWrite(lightPin[6], HIGH);
    part = 5;
  }

  if (part == 0 && showing == false) {
    for (int i = 0; i < 8; i++) {
      if (parts1[i] == 0) {
        r0 = 0;
        r1 = 0;
        r2 = 0;
        tone(buzzerPin, melody[0], 800);
      } else if (parts1[i] == 1) {
        r0 = 1;
        r1 = 0;
        r2 = 0;
        tone(buzzerPin, melody[1], 800);
      } else if (parts1[i] == 2) {
        r0 = 0;
        r1 = 1;
        r2 = 0;
        tone(buzzerPin, melody[2], 800);
      }
      else if (parts1[i] == 3) {
        r0 = 1;
        r1 = 1;
        r2 = 0;
        tone(buzzerPin, melody[3], 800);
      } else if (parts1[i] == 4) {
        r0 = 0;
        r1 = 0;
        r2 = 1;
        tone(buzzerPin, melody[4], 800);
      } else if (parts1[i] == 5) {
        r0 = 1;
        r1 = 0;
        r2 = 1;
        tone(buzzerPin, melody[5], 800);
      } else if (parts1[i] == 6) {
        r0 = 0;
        r1 = 1;
        r2 = 1;
        tone(buzzerPin, melody[6], 800);
      }
      digitalWrite(2, r0);
      digitalWrite(3, r1);
      digitalWrite(4, r2);

      delay(1000);
    }

    iCount = 0;
    showing = true;
  } else if (part == 1 && showing == false) {
    for (int i = 0; i < 8; i++) {
      if (parts2[i] == 0) {
        r0 = 0;
        r1 = 0;
        r2 = 0;
        tone(buzzerPin, melody[0], 800);
      } else if (parts2[i] == 1) {
        r0 = 1;
        r1 = 0;
        r2 = 0;
        tone(buzzerPin, melody[1], 800);
      } else if (parts2[i] == 2) {
        r0 = 0;
        r1 = 1;
        r2 = 0;
        tone(buzzerPin, melody[2], 800);
      }
      else if (parts2[i] == 3) {
        r0 = 1;
        r1 = 1;
        r2 = 0;
        tone(buzzerPin, melody[3], 800);
      } else if (parts2[i] == 4) {
        r0 = 0;
        r1 = 0;
        r2 = 1;
        tone(buzzerPin, melody[4], 800);
      } else if (parts2[i] == 5) {
        r0 = 1;
        r1 = 0;
        r2 = 1;
        tone(buzzerPin, melody[5], 800);
      } else if (parts2[i] == 6) {
        r0 = 0;
        r1 = 1;
        r2 = 1;
        tone(buzzerPin, melody[6], 800);
      }
      digitalWrite(2, r0);
      digitalWrite(3, r1);
      digitalWrite(4, r2);

      delay(1000);
    }
    showing = true;
  } else if (part == 2 && showing == false) {
    for (int i = 0; i < 8; i++) {
      if (parts3[i] == 0) {
        r0 = 0;
        r1 = 0;
        r2 = 0;
        tone(buzzerPin, melody[0], 800);
      } else if (parts3[i] == 1) {
        r0 = 1;
        r1 = 0;
        r2 = 0;
        tone(buzzerPin, melody[1], 800);
      } else if (parts3[i] == 2) {
        r0 = 0;
        r1 = 1;
        r2 = 0;
        tone(buzzerPin, melody[2], 800);
      }
      else if (parts3[i] == 3) {
        r0 = 1;
        r1 = 1;
        r2 = 0;
        tone(buzzerPin, melody[3], 800);
      } else if (parts3[i] == 4) {
        r0 = 0;
        r1 = 0;
        r2 = 1;
        tone(buzzerPin, melody[4], 800);
      } else if (parts3[i] == 5) {
        r0 = 1;
        r1 = 0;
        r2 = 1;
        tone(buzzerPin, melody[5], 800);
      } else if (parts3[i] == 6) {
        r0 = 0;
        r1 = 1;
        r2 = 1;
        tone(buzzerPin, melody[6], 800);
      }
      digitalWrite(2, r0);
      digitalWrite(3, r1);
      digitalWrite(4, r2);

      delay(1000);
    }
    showing = true;
  } else if (part == 3 && showing == false) {
    for (int i = 0; i < 6; i++) {
      if (parts4[i] == 0) {
        r0 = 0;
        r1 = 0;
        r2 = 0;
        tone(buzzerPin, melody[0], 800);
      } else if (parts4[i] == 1) {
        r0 = 1;
        r1 = 0;
        r2 = 0;
        tone(buzzerPin, melody[1], 800);
      } else if (parts4[i] == 2) {
        r0 = 0;
        r1 = 1;
        r2 = 0;
        tone(buzzerPin, melody[2], 800);
      }
      else if (parts4[i] == 3) {
        r0 = 1;
        r1 = 1;
        r2 = 0;
        tone(buzzerPin, melody[3], 800);
      } else if (parts4[i] == 4) {
        r0 = 0;
        r1 = 0;
        r2 = 1;
        tone(buzzerPin, melody[4], 800);
      } else if (parts4[i] == 5) {
        r0 = 1;
        r1 = 0;
        r2 = 1;
        tone(buzzerPin, melody[5], 800);
      } else if (parts4[i] == 6) {
        r0 = 0;
        r1 = 1;
        r2 = 1;
        tone(buzzerPin, melody[6], 800);
      }
      digitalWrite(2, r0);
      digitalWrite(3, r1);
      digitalWrite(4, r2);

      delay(1000);
    }
    showing = true;
  }

  // Get the currently touched pads

  currtouched = cap.touched();

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      touching = i;
      released = false;
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
      touching = -1;
      released = true;
    }
  }
  Serial.println(iCount);

  // reset our state
  lasttouched = currtouched;

  if (showing == true) {
    if (touching == 0) {
      r0 = 0;
      r1 = 0;
      r2 = 0;
      tone(buzzerPin, melody[0], 125);
      lastPlayed = 0;
    } else if (touching == 1) {
      r0 = 1;
      r1 = 0;
      r2 = 0;
      tone(buzzerPin, melody[1], 125);
      lastPlayed = 1;
    } else if (touching == 2) {
      r0 = 0;
      r1 = 1;
      r2 = 0;
      tone(buzzerPin, melody[2], 125);
      lastPlayed = 2;
    }
    else if (touching == 3) {
      r0 = 1;
      r1 = 1;
      r2 = 0;
      tone(buzzerPin, melody[3], 125);
      lastPlayed = 3;
    } else if (touching == 4) {
      r0 = 0;
      r1 = 0;
      r2 = 1;
      tone(buzzerPin, melody[4], 125);
      lastPlayed = 4;
    } else if (touching == 5) {
      r0 = 1;
      r1 = 0;
      r2 = 1;
      tone(buzzerPin, melody[5], 125);
      lastPlayed = 5;
    } else if (touching == 6) {
      r0 = 0;
      r1 = 1;
      r2 = 1;
      tone(buzzerPin, melody[6], 125);
      lastPlayed = 6;
    } else {
      r0 = 1;
      r1 = 1;
      r2 = 1;
    }

    if (part == 0) {
      if (released == true && lastPlayed == parts1[iCount]) {
        iCount++;
        released = false;
        if (iCount > 7) {
          delay(1000);
          showing = false;
          part = 1;
        }
      } else if (released == true) {
        iCount = 0;
        released = false;
        showing = false;
      }
    } else if (part == 1) {
      if (released == true && lastPlayed == parts2[iCount]) {
        iCount++;
        released = false;
        if (iCount > 7) {
          delay(1000);
          showing = false;
          part = 2;
        }
      } else if (released == true) {
        iCount = 0;
        released = false;
        showing = false;
      }
    } else if (part == 2) {
      if (released == true && lastPlayed == parts3[iCount]) {
        iCount++;
        released = false;
        if (iCount > 7) {
          delay(1000);
          showing = false;
          part = 3;
        }
      } else if (released == true) {
        iCount = 0;
        released = false;
        showing = false;
      }
    } else if (part == 3) {
      if (released == true && lastPlayed == parts4[iCount]) {
        iCount++;
        released = false;
        if (iCount > 5) {
          delay(1000);
          showing = false;
          part = 4;
        }
      } else if (released == true) {
        iCount = 0;
        released = false;
        showing = false;
      }
    }


    digitalWrite(2, r0);
    digitalWrite(3, r1);
    digitalWrite(4, r2);
  }


  if (part == 0 || part == 1 || part == 2 || part == 3) {
    for (int i = 0; i < 7; i++) {
      digitalWrite(lightPin[i], HIGH);
    }

  }

}






