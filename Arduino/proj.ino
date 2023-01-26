// include the library code:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const float Amic1 = A1;
const float Amic2 = A2;
const float Amic3 = A3;
const int r1 = 9;
const int r2 = 8;
const int r3 = 7;
const int y = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;




void setup() {
  
 Serial.begin(9600); 
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(y,OUTPUT);
    // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
 // EXTRA NOISE ON:
 // GRND    0
 // FLR1    5
 // FLR2    10


 
 }

void loop() {
  int sens1 = map(analogRead(Amic1), 0,1023, 0, 100);
  int sens2 = map(analogRead(Amic2), 0,1023, 0, 100);
  int sens3 = map(analogRead(Amic3), 0,1023, 0, 100);
  Serial.print(sens1);
if(sens1 > 50){// only s0 high
  if(sens2 > 50){//s0, s2 high
    if(sens3 > 50){// all of them are high
      digitalWrite(r1,HIGH);
      counter1();
      digitalWrite(r2,HIGH);
      counter2();
      digitalWrite(r3,HIGH);
      counter3();
    }
    else{
      digitalWrite(r1,HIGH);
      counter1();
      digitalWrite(r2,HIGH);
      counter2();
      digitalWrite(r3,LOW);
      count3 = 0; // clear count3 because there is no noise therefore no time record for noise
      
    }
  }
  else if(sens3 > 50)// s0,s2 high
  {
     digitalWrite(r1,HIGH);
     counter1();
     digitalWrite(r2,LOW);
     count2 = 0; 
     digitalWrite(r3,HIGH); 
     counter3();
  }
  else{// only s0 high
      digitalWrite(r1,HIGH);
      counter1();
      digitalWrite(r2,LOW);
     count2 = 0; 
     //digitalWrite(y, LOW);      
      digitalWrite(r3,LOW);
     count3 = 0; 

  }
}

else if(sens2 > 50){ // s0 low
  if(sens3 > 50){// s1,s2 high
      digitalWrite(r1,LOW);
      count1 = 0; 
      //digitalWrite(y, LOW);      
      digitalWrite(r2,HIGH);
      counter2();
      digitalWrite(r3,HIGH);
      counter3();
    
  }
  else{// only s2 high
      digitalWrite(r1,LOW);
     count1 = 0; 
     //digitalWrite(y, LOW);      
      digitalWrite(r2,HIGH);
      counter2();
      digitalWrite(r3,LOW);
     count3 = 0; 
     //digitalWrite(y, LOW);      
  }
  
}

else if(sens3 > 50 ){// only s2 high
      digitalWrite(r1,LOW);
     count1 = 0; 
     //digitalWrite(y, LOW);      
      digitalWrite(r2,LOW);
     count2 = 0; 
     //digitalWrite(y, LOW);      
      digitalWrite(r3,HIGH);
      counter3();
}

else{ //all of them are low
      digitalWrite(r1,LOW);
     count1 = 0; 
     digitalWrite(y, LOW);      
      digitalWrite(r2,LOW);
     count2 = 0; 
     digitalWrite(y, LOW);      
      digitalWrite(r3,LOW);
     count3 = 0; 
     digitalWrite(y, LOW);      
}
delay(30);

while( count1 < 6){
        if (count1 == 0)
        {
         lcd.setCursor(0,1); 
         lcd.print("    ");// to clear the lcd if the count is zero unless it is displayed on lcd
        }
         else{
         lcd.setCursor(0,1);
         lcd.print("-");
         lcd.print(count1);// to display the counter on lcd
          lcd.print("-");
        lcd.print(" "); // to make the space after counter empty
         }
        break;
}

while( count2 < 6){
           if (count2 == 0)
        {
         lcd.setCursor(5,1);
         lcd.print("     "); 
        }
       else {
        lcd.setCursor(5,1);
        lcd.print(" -");
       lcd.print(count2);
       lcd.print("- ");} 

       break; 
}
while( count3 < 6){
           if (count3 == 0){
          lcd.setCursor(10,1);
          lcd.print("      ");
         }

         else{
         
          lcd.setCursor(10,1);
         lcd.print("   ");// clear
          lcd.print("-");
         lcd.print(count3);
          lcd.print("-");
         }
         break;
}

if((count1 ==0) &&(count2==0) && (count3)==0){
  lcd.clear();
}


}


void counter1(){
         if(count1>5){
         lcd.setCursor(0,0);
         lcd.print("EXTRA NOISE ON:");
         delay(10);

        lcd.setCursor(0,1);
        lcd.print("GRND");
        digitalWrite(y, HIGH);
       }
       else{
        count1++; // increase time record
       }
}

void counter2(){
         if(count2>5){
         lcd.setCursor(0,0);
         lcd.print("EXTRA NOISE ON:");
         delay(10);
         lcd.setCursor(5,1);
         lcd.print("FLOR1");
         delay(10); 
         digitalWrite(y, HIGH);
         }
         
           else{
        count2++;     
       }
}

void counter3(){
         if(count3>5){
         lcd.setCursor(0,0);
         lcd.print("EXTRA NOISE ON:");
         
         delay(10);
         lcd.setCursor(10,1);
         lcd.print(" FLOR2");
         digitalWrite(y, HIGH);
          }
         else{
         count3++; 
       }
}
