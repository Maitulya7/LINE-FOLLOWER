#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(2, 3); // RX, TX
int ir1=A0, ir2=A1, ir3=A2;


#define en1 10
#define en2 9

#define m1in1 9
#define m1in2 8

#define m2in1 7
#define m2in2 6

#define ir_left A2
#define ir_right A0
#define ir_center A1

int bt_data; // variable to receive data from the serial port
int Speed = 130;  

int mode=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3,INPUT);
  Serial.begin(9600);
  
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);

  pinMode(m1in1, OUTPUT);
  pinMode(m1in2, OUTPUT);

  pinMode(m2in1, OUTPUT);
  pinMode(m2in2, OUTPUT);

  digitalWrite(en1, 1);
  digitalWrite(en2, 1);
  
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

analogWrite(en1, Speed); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, Speed); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

if(mode==0){     
//===============================================================================
//                          App key Control Command manual 
//=============================================================================== 
     if(bt_data == 1){forword(); }  // if the bt_data is '1' the DC motor will go forward
else if(bt_data == 2){backword();}  // if the bt_data is '2' the motor will Reverse
else if(bt_data == 3){left_();}  // if the bt_data is '3' the motor will turn left
else if(bt_data == 4){right_();} // if the bt_data is '4' the motor will turn right
else if(bt_data == 5){Stop(); }     // if the bt_data '5' the motor will Stop

//===============================================================================
//                          Voice Control Command
//===============================================================================    
else if(bt_data == 6){left_();  delay(400);  bt_data = 5;}
else if(bt_data == 7){right_(); delay(400);  bt_data = 5;}
}
else{

void loop() {
int left = digitalRead(ir_left);
int right = digitalRead(ir_right);
int center = digitalRead(ir_center);

if ( left==0 && center==0 && right==0){
  forward();
}

else if ( left==0 && center==0 && right==1){
  left_();
  }
  
else if (left==0 && center==1 && right==0){
  forward();
  }

else if (left==0 && center==1 && right==1){
    forward();
    }
 else if (left==1 && center==0 && right==0){
    right_();
    }
 else if (left==1 && center==0 && right==1){
    forward();
    }
 else if (left==1 && center==1 && right==0){
    forward();
    }
 else if (left==1 && center==1 && right==1){
    forward();
    }

 }

}


void stop_(){
  Serial.println("0,0 : 0,0");   
  digitalWrite(m1in1, 0);
  digitalWrite(m1in2, 0);
  
  digitalWrite(m2in1, 0);
  digitalWrite(m2in2, 0);
}

void forward(){
  Serial.println("0,1 : 0,1");
  digitalWrite(m1in1, 1);
  digitalWrite(m1in2, 0);
  
  digitalWrite(m2in1, 1);
  digitalWrite(m2in2, 0);
}


void backward(){
  digitalWrite(m1in1, 0);
  digitalWrite(m1in2, 1);

  digitalWrite(m2in1, 0);
  digitalWrite(m2in2, 1);
}

void right_(){
  digitalWrite(m1in1, 1s);
  digitalWrite(m1in2, 0);

  digitalWrite(m2in1, 0);
  digitalWrite(m2in2, 1);
}

void left_(){
  digitalWrite(m1in1, 0);
  digitalWrite(m1in2, 1);

  digitalWrite(m2in1, 1);
  digitalWrite(m2in2, 0);
}
