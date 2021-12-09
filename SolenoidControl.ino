short REV_BUTTON = 5;
int baudrate = 115200; // If you change this you must change it on the Xbee modules as well
#define HWSERIAL Serial5 // Xbee module connected to the teensy board
String message = ""; // Do not change this
String gift = ""; // Do not change this
String incomingByte;
bool instructionFlag = false; // Raised when a instruction has been received
short milliSecDelay = 100; // How long do you want to push the button. It is not recommened to give
                           // power to a solenoid for more than two seconds because it can cause
                           // over heating

void setup() {
  pinMode(REV_BUTTON, OUTPUT); // This must be done for all other buttons too

  HWSERIAL.begin(baudrate); // This serial port is being used to receive transmissions from the xbee module
  Serial.begin(9600); // This serial port is for transmitting & receiving from the computer (debugging purposes)
}

void loop() {

  XbeeMessage(); // Prints the message and if a command is sent then it deals with it
  
}

void XbeeMessage() {
  if (HWSERIAL.available() > 0) {
    incomingByte = HWSERIAL.read(); // Read the character in the Serial Port
    message = incomingByte;
    if (!instructionFlag) {
      Serial.print(incomingByte);
    }
    BufferSystem(message);
  }  
}

void BufferSystem(String message){
  //Serial.println(message);
  //gift += message;
  //Serial.print(gift);

  if (message == ";") {
    instructionFlag = false;
    Instruction(gift);
    gift = "";
  }

  if (instructionFlag) {
    gift += message;
  }

  if (message == "$"){
    instructionFlag = true;
  }

  
}

void Instruction(String str) {
  Serial.println(str);
  digitalWrite(str.toInt(), LOW);
  delay(milliSecDelay);
  digitalWrite(str.toInt(), HIGH);
  
}
