#define Button1Pin A0     
#define Button2Pin A1    
#define Button3Pin A2     
#define Button4Pin A3     
#define Sensor1Pin A4    
#define Sensor2Pin A5    
#define Sensor3Pin 12     
#define Sensor4Pin 13     
#define OutputQ1Pin 5    
#define OutputQ2Pin 4     

//variables to store button input
boolean button0 = 0;
boolean button1 = 0;
boolean button3 = 0;
//variables to store sensor input
boolean sensor0 = 0;
boolean sensor1 = 0;
boolean sensor3 = 0;
//variables to store state of state machine
boolean X1 = 0;
boolean X2 = 0;
boolean X3 = 0;
boolean X4 = 0;
//variables to store output for the motor
boolean Q1 = 0;
boolean Q2 = 0;


//function that read input of sensors and buttons
void readInput(){
  button0 = digitalRead(Button1Pin);
  button1 = digitalRead(Button2Pin);
  button3 = digitalRead(Button4Pin);

  sensor0 = digitalRead(Sensor1Pin);
  sensor1 = digitalRead(Sensor2Pin);
  sensor3 = digitalRead(Sensor4Pin);
}

//setup function to set read/write modes for pins
void setup(){
  pinMode(Button1Pin, INPUT);
  pinMode(Button2Pin, INPUT);
  pinMode(Button4Pin, INPUT);

  pinMode(Sensor1Pin, INPUT);
  pinMode(Sensor2Pin, INPUT);
  pinMode(Sensor4Pin, INPUT);

  pinMode(OutputQ1Pin, OUTPUT);
  pinMode(OutputQ2Pin, OUTPUT);
}

//function to calculate the next state;
void calculateState(){
  boolean X1copy = 0;
  boolean X2copy = 0;
  boolean X3copy = 0;
  boolean X4copy = 0;

  //calculate next state based on previous state and input
  X1copy = (!X1 && !X2 && X3 && X4 && button0) 
            || (!X1 && !X2 && X3 && X4 && button1)
            || (X1 && !X2 && !X3 && !X4 && !sensor1)
            || (X1 && !X2 && !X3 && X4  && !sensor0);

  X2copy = (!X1 && !X2 && !X3 && X4 && button1)
           || (!X1 && !X2 && !X3 && X4 && button3)
           || (!X1 && !X2 && X3 && !X4 && button0)
           || (!X1 && !X2 && X3 && !X4 && button3)
           || (!X1 && X2 && !X3 && !X4 && !sensor1)
           || (!X1 && X2 && !X3 && X3 && !sensor3)
           || (!X1 && X2 && X3 && !X4 && !sensor3)
           || (!X1 && X2 && X3 && X4 && sensor0);

  X3copy = (!X1 && !X2 && !X3 && !X4 && sensor3)
           || (!X1 && !X2 && X3 && !X4 && button0)
           || (!X1 && !X2 && X3 && !X4 && button3)
           || (!X1 && X2 && !X3 && !X4 && sensor1)
           || (!X1 && X2 && !X3 && X4 &&  sensor3)
           || (!X1 && X2 && X3 && !X4)
           || (!X1 && X2 && X3 && X4 && !sensor0)
           || (X1 && !X2 && !X3 && !X4 && sensor1)
           || (!X1 && !X2 && X3 && !X4 && !button0 && !button3)
           || (!X1 && !X2 && X3 && X4 && !button0 && !button1);

  X4copy = (!X1 && !X2 && !X3 && !X4 && sensor3)
           || (!X1 && !X2 && !X3 && X4 && button3)
           || (!X1 && !X2 && X3 && !X4 && button0)
           || (!X1 && !X2 && X3 && X4 && button0)
           || (!X1 && X2 && !X3 && X4)
           || (!X1 && X2 && X3 && !X4 && sensor3)
           || (!X1 && X2 && X3 && X4)
           || (X1 && !X2 && !X3 && X4)
           || (!X1 && !X2 && !X3 && X4 && !button1 && button3)
           || (!X1 && !X2 && X3 && X4 && !button0 && !button1);

  //make next state current state 
  X1 = X1copy;
  X2 = X2copy;
  X3 = X3copy;
  X4 = X4copy;
}

//function to calculate output for the elevator motor
void calculateOutput(){
  Q1 = (!X1 && X2 && X3 && X4)
       || (X1 && !X2 && !X3);
  
  Q2 = (!X1 && !X2 && !X3 && X4)
       || (!X1 && !X2 && X3);
}

void loop() {
  readInput();
  calculateState();
  calculateOutput();
}
