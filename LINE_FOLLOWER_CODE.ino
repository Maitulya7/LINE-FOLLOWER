#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(2, 3); // RX, TX

#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in2 
#define in3 7 //Motor2  L298 Pin in3 
#define in4 6 //Motor2  L298 Pin in4 
#define enB 5 //Enable2 L298 Pin enB 

#define R_S A0 //ir sensor Right
#define C_S A1 //ir sensor center
#define L_S A2 //ir sensor Left

int bt_data; // variable to receive data from the serial port
int Speed = 130;  

int mode=0;

void setup(){ // put your setup code here, to run once

pinMode(R_S, INPUT); // declare if sensor as input 
pinMode(C_S, INPUT); // declare if sensor as input  
pinMode(L_S, INPUT); // declare ir sensor as input

pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

Serial.begin(9600); // start serial communication at 9600bps , The value 9600 is called the 'baud rate' of the connection. This is how fast the data is to be sent.
BT_Serial.begin(9600); 
delay(500);
}
//===============================================================================
//                         Bluetooth commands
//=============================================================================== 

void loop(){  
  
if(BT_Serial.available() > 0){  //if some date is sent, reads it and saves in state     
bt_data = BT_Serial.read();      
if(bt_data > 20){Speed = bt_data;}      
}

     if(bt_data == 8){mode=1; Speed=130;} //Auto Line Follower Command  
else if(bt_data == 9){mode=0; Stop();}    //Manual Android Application Control Command

analogWrite(enA, Speed); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, Speed); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

if(mode==0){     
//===============================================================================
//                          App key Control Command manual 
//=============================================================================== 
     if(bt_data == 1){forword(); }  // if the bt_data is '1' the DC motor will go forward
else if(bt_data == 2){backword();}  // if the bt_data is '2' the motor will Reverse
else if(bt_data == 3){turnLeft();}  // if the bt_data is '3' the motor will turn left
else if(bt_data == 4){turnRight();} // if the bt_data is '4' the motor will turn right
else if(bt_data == 5){Stop(); }     // if the bt_data '5' the motor will Stop

//===============================================================================
//                          Voice Control Command
//===============================================================================    
else if(bt_data == 6){turnLeft();  delay(400);  bt_data = 5;}
else if(bt_data == 7){turnRight(); delay(400);  bt_data = 5;}
}else{    
//===============================================================================
//                          Line Follower Control auto 
//===============================================================================     
if ((digitalRead(L_S) == 0)&&(digitalRead(C_S) == 1)&&(digitalRead(R_S) == 0)){forword();} // LEFT AND RIGHT SENSOR IN ON WHITE , AND CENTER SENSOR IS ON BLACK 

//if ((digitalRead(L_S) == 0)&&(digitalRead(C_S) == 0)&&(digitalRead(R_S) == 0)){forward();} // LEFT AND CENTER SENSOR IS ON BLACK , AND RIGHT SENSOR IS ON WHITE 
if ((digitalRead(L_S) == 1)&&(digitalRead(C_S) ==1)&&(digitalRead(R_S) == 1)) {forword();} // RIGHT AND CENTER SENSOR IS ON WHITE , AND LEFT SENSOR IS ON BLACK 


if ((digitalRead(L_S) == 1)&&(digitalRead(C_S) == 1)&&(digitalRead(R_S) == 0)){turnLeft();} // CENTER AND RIGHT SENSOR IS ON BLACK , AND LEFT SENSOR IS ON WHITE 
if ((digitalRead(L_S) == 1)&&(digitalRead(C_S) == 0)&&(digitalRead(R_S) == 0)){turnLeft();} // CENTER AND LEFT SENSOR IS ON WHITE , AND RIGHT SENSOR IS ON BLACK 

if ((digitalRead(L_S) == 0)&&(digitalRead(C_S) == 1)&&(digitalRead(R_S) == 1)){turnRight();} // LEFT , RIGHT AND CENTER SENSOR IS ON BLACK 
if ((digitalRead(L_S) == 0)&&(digitalRead(C_S) == 0)&&(digitalRead(R_S) == 1)){turnRight();}
} 

delay(10);
}

void forword(){  //forword
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void backword(){ //backword
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 
}

void turnRight(){ //turnRight
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin  
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void turnLeft(){ //turnLeft
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW); //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
}
