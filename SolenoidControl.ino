short REV_BUTTON = 5; // Number reflects the pin # on the Teensy
int baudrate = 115200; // If you change this you must change it on the Xbee modules as well
#define HWSERIAL Serial5 // Xbee module connected to the teensy board
String message = ""; // Do not change this
String gift = ""; // Do not change this
String incomingByte; // Do not change this
bool instructionFlag = false; // Raised when a instruction has been received
short milliSecDelay = 100; // How long do you want to push the button. It is not recommened to give
                           // power to a solenoid for more than two seconds because it can cause
                           // over heating

void setup() {
  // Setup Output Pins
  pinMode(REV_BUTTON, OUTPUT); // This must be done for all other buttons too

  // Setup Serial Communications
  HWSERIAL.begin(baudrate); // This serial port is being used to receive transmissions from the xbee module
  Serial.begin(9600); // This serial port is for transmitting & receiving from the computer (debugging purposes)
}

void loop() {
  XbeeMessage(); // Polling for messages
}

// This function waits until something is received in the serial ports
// then it prints it out and sends that character through the BufferSystem 
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



// Sorts through the incoming characters being sent through the serial port
// If the money sign is received then the system knows the rest of the 
// characters are an instruction up until we receive a semi-colon
void BufferSystem(String message){
  // End of the instruction
  // Therefore we clear the variable that holds our instruction
  if (message == ";") {
    instructionFlag = false;
    Instruction(gift);
    gift = "";
  }

  // If the instruction flag is up save all the characters to a variable
  if (instructionFlag) {
    gift += message;
  }

  // Raise the instruction flag if you send a money sign
  if (message == "$"){
    instructionFlag = true;
  }

  
}

// The String variable str represents the instruction
// At the moment the only thing and instruction does is
// change a pin #'s ouput from HIGH to LOW for a small amount of time
void Instruction(String str) {
  Serial.println(str);
  digitalWrite(str.toInt(), LOW);
  delay(milliSecDelay);
  digitalWrite(str.toInt(), HIGH);
  
}
