#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial bluetooth(10, 11); // RX, TX

String readString;
#define MOTOR_A_PWM 5 // Motor A PWM Speed
#define MOTOR_A_DIR 7 // Motor A Direction

#define MOTOR_B_PWM 6 // Motor B PWM Speed
#define MOTOR_B_DIR 8 // Motor B Direction
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);  
  delay(100);
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  
  digitalWrite( MOTOR_A_DIR, LOW );
  digitalWrite( MOTOR_A_PWM, LOW );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
}

void loop() {

  StaticJsonBuffer<200> jsonBuffer;
  while (bluetooth.available()) {
    char c = bluetooth.read();  
    if (c == '\n') {
      break;
    }  
    readString += c; 
    delay(1);
  } 

  if (readString.length() >0) {
    Serial.println(readString); 
    JsonObject& root = jsonBuffer.parseObject(readString);
    if (!root.success()) {
      Serial.println("parseObject() failed");
      return;
   }
   const String angle = root["angle"];
   
   const String _force = root["force"];
   int force = _force.toInt();
   force = (force*255)/100;
   const char* A = root["A"];
   const char* B = root["B"];
   const char* C = root["C"];
   const char* D = root["D"];
  
     if(angle == "up") up(force); 
     if(angle == "down") down(force); 
     if(angle == "left") left(force); 
     if(angle == "right") right(force); 
     if(angle == "0") stop(); 
   

 
   readString=""; 
   
  
  }
}


void up(int force){
   Serial.println("up");

    Serial.println(force);
   digitalWrite( MOTOR_A_DIR, HIGH );
   analogWrite( MOTOR_A_PWM, -force );
   digitalWrite( MOTOR_B_DIR, HIGH );
   analogWrite( MOTOR_B_PWM, -force );
}
void down(int force){
   Serial.println("down");
   digitalWrite( MOTOR_A_DIR, LOW );
   analogWrite( MOTOR_A_PWM,  force );
   digitalWrite( MOTOR_B_DIR, LOW );
   analogWrite( MOTOR_B_PWM, force );
}
void left(int force){
   Serial.println("left");
   digitalWrite( MOTOR_A_DIR, LOW );
   digitalWrite( MOTOR_A_PWM, LOW );
   digitalWrite( MOTOR_B_DIR, HIGH );
   analogWrite( MOTOR_B_PWM, -force );
}
void right(int force){
   Serial.println("right");
   digitalWrite( MOTOR_A_DIR, HIGH );
   analogWrite( MOTOR_A_PWM, -force );
   digitalWrite( MOTOR_B_DIR, LOW );
   digitalWrite( MOTOR_B_PWM, LOW );
}


void stop(){
   Serial.println("stop");
   digitalWrite( MOTOR_A_DIR, LOW );
   digitalWrite( MOTOR_A_PWM, LOW );
   digitalWrite( MOTOR_B_DIR, LOW );
   digitalWrite( MOTOR_B_PWM, LOW );
}
