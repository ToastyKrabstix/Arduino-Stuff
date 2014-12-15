int line1 = 5;
int line2 = 6;
int line3 = 7;
int LED = 13;
int reads[3];
int i;

int LeftMotor1 = 10;
int LeftMotor2 = 11;
int RightMotor1 = 9;
int RightMotor2 = 8;
char pathing[30] = {};
int pathlength;
int startedpath;
void setup(){
 Serial.begin(9600);
 pinMode(LeftMotor1, OUTPUT); 
 pinMode(LeftMotor2, OUTPUT); 
 pinMode(RightMotor1, OUTPUT); 
 pinMode(RightMotor2, OUTPUT); 
 
 pinMode(line1, INPUT);
 pinMode(line2, INPUT);
 pinMode(line3, INPUT);
 pathlength=0;
 pathing[pathlength] = 'Z';
 
 pinMode(13, OUTPUT);
 
 digitalWrite(13, HIGH);
 delay(1000);
 digitalWrite(13, LOW);
 delay(1000);
 digitalWrite(13, HIGH);
 delay(1000);
 digitalWrite(13, LOW);
 delay(1000);
 
}

void loop(){
 SenseRead();  
  if(reads[0] == 0 && reads[1] == 1 && reads[2] == 0){ 
    
   do{
   //Serial.print("Correct Path!\n"); 
   analogWrite(LeftMotor1, 150); 
   analogWrite(LeftMotor2, 150);
 
   analogWrite(RightMotor1, 150); 
   analogWrite(RightMotor2, 150);
   delay(5);
   SenseRead();
   if (reads[0] == 1 && reads[1] == 0 && reads[2] == 0){
   //Serial.print("Bump Left!\n");
   analogWrite(LeftMotor1, 200); 
   analogWrite(LeftMotor2, 200);
 
   analogWrite(RightMotor1, 0); 
   analogWrite(RightMotor2, 0);
    delay(50);
  }
  
  else if (reads[0] == 0 && reads[1] == 0 && reads[2] == 1){
  //Serial.print("Bump Right!\n"); 
   analogWrite(LeftMotor1, 0); 
   analogWrite(LeftMotor2, 0);
 
 analogWrite(RightMotor1, 200); 
 analogWrite(RightMotor2, 200);
 delay(50);
  }
   
   SenseRead();
   deadEnd();
  }while(reads[0] == 0 && reads[1] == 1 && reads[2] == 0);
  }else{
   SenseRead();
   Solving();
   SenseRead();
   //deadEnd();
  }
}

void SenseRead(){
 reads[0] = digitalRead(line1);
  reads[1] = digitalRead(line2);
  reads[2] = digitalRead(line3); 
}


void Solving(){
  
  
  if (reads[0] == 1 && reads[1] == 1 && reads[2] == 0){

   //Serial.print("Turn Right!\n"); 
   if(pathing[pathlength] != 'R'){
     pathlength++;
   pathing[pathlength] = 'R';
   }
   
   SenseRead();
   do{
   analogWrite(LeftMotor1, 0); 
   analogWrite(LeftMotor2, 0);
 
   analogWrite(RightMotor1, 150); 
   analogWrite(RightMotor2, 150);
   //delay(300);
   SenseRead();
   }while(reads[0] != 0 && reads[1] != 1 && reads[2] != 0);
  }
  
  if (reads[0] == 0 && reads[1] == 1 && reads[2] == 1){
   //Serial.print("Turn Left!\n"); 
   if(pathing[pathlength] != 'L'){
     pathlength++;
   pathing[pathlength] = 'L';
   }
   SenseRead();
   do{
   analogWrite(LeftMotor1, 150); 
   analogWrite(LeftMotor2, 150);
 
   analogWrite(RightMotor1, 0); 
   analogWrite(RightMotor2, 0);
   //delay(300);
   SenseRead();
   }while(reads[0] != 0 && reads[1] != 1 && reads[2] != 0);
  }
  
   if (reads[0] == 1 && reads[1] == 1 && reads[2] == 1){
   //Serial.print("2 Possibilities\n"); 
   if(pathing[pathlength] != 'L'){
   pathlength++;
   pathing[pathlength] = 'L';
   }
   SenseRead();
   do{
   analogWrite(LeftMotor1, 150); 
   analogWrite(LeftMotor2, 150);
 
   analogWrite(RightMotor1, 0); 
   analogWrite(RightMotor2, 0);
   //delay(300);
   SenseRead();
   }while(reads[0] != 0 && reads[1] != 1 && reads[2] != 0);
  }
  
   if(reads[0] == 1 && reads[1] == 0 && reads[2] == 1){
    if(pathing[pathlength] != 'Q'){
   pathlength++;
   pathing[pathlength] = 'Q';
   }
   SenseRead();
   do{
    analogWrite(LeftMotor1, 0); 
   analogWrite(LeftMotor2, 0);
 
   analogWrite(RightMotor1, 0); 
   analogWrite(RightMotor2, 0);
   SenseRead();
   }while(reads[0] != 0 && reads[1] != 1 && reads[2] != 0);
  }
  delay(100);
  Serial.print(pathing);
  Serial.print("\n");
}

void deadEnd(){
 if (reads[0] == 0 && reads[1] == 0 && reads[2] == 0){
   //Serial.print("Turn 180!\n"); 
   
   if(pathing[pathlength] != 'B'){
     pathlength++;
   pathing[pathlength] = 'B';
   }
   SenseRead();
    do{
   analogWrite(LeftMotor1, 150); 
   analogWrite(LeftMotor2, 150);
 
   analogWrite(RightMotor1, 150); 
   analogWrite(RightMotor2, 0);
   SenseRead();
   }while(reads[0] != 0 && reads[1] != 1 && reads[2] != 0);
  } 
  
}
