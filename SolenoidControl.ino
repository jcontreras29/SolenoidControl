short REV_BUTTON = 5;
short led = 13;
int baudrate = 115200; // If you change this you must change it on the Xbee modules as well
#define HWSERIAL Serial5 // Xbee module connected to the teensy board
//char Buffer[32];
String message = "";
String gift = "";
bool instructionFlag = false;
short milliSecDelay = 100;

void setup() {
  pinMode(REV_BUTTON, OUTPUT);
  pinMode(led, OUTPUT);

  HWSERIAL.begin(baudrate); // This serial port is being used to receive transmissions from the xbee module
  Serial.begin(9600); // This serial port is for transmitting & receiving from the computer (debugging purposes)
}

void loop() {

  XbeeMessage(); // Prints the message received to the serial port and then saves it as a variable
  
}

void XbeeMessage() {
  String incomingByte;
  if (HWSERIAL.available() > 0) {
    incomingByte = HWSERIAL.read();
    message = incomingByte;
    if (!instructionFlag) {
      Serial.print(incomingByte);
    }
    // Stage 2
    BufferSystem(message);

    
    // Stage 1
    //Serial.print(message);
  }
//  if (message.equals("5")) {
//    digitalWrite(pin, LOW);
//    delay(100);
//    digitalWrite(pin, HIGH);
//  }

  
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
