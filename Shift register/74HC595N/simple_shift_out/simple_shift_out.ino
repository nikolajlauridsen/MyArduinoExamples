// Master reset is pulled high and output enable is low

#define clk 5
#define data 3
#define latch 4

byte boardPattern;

void setup() {
  // put your setup code here, to run once:
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  digitalWrite(clk, LOW);
  digitalWrite(data, LOW);
  digitalWrite(latch, LOW);
}

void loop() {

  boardPattern = 1;
  // Make single point fly to the left
  for(int i=0; i<8; i++){
    shiftOut(boardPattern);
    boardPattern = boardPattern<<1;
    delay(25);  
  }
  // Make single pint fly to the right
  boardPattern = 128;
  for(int i=0; i<8; i++){
    shiftOut(boardPattern);
    boardPattern = boardPattern>>1;
    delay(25);  
  }
  // Fill bar
  boardPattern = 1;
  for(int i=0; i<8; i++){
    shiftOut(boardPattern);
    boardPattern = boardPattern*2+1;
    delay(25);  
  }
  // Empty bar
  for(int i=0; i<8; i++){
    shiftOut(boardPattern);
    boardPattern = boardPattern>>1;
    delay(25);  
  }
  // Fill bar
  boardPattern = 1;
  for(int i=0; i<8; i++){
    shiftOut(boardPattern);
    boardPattern = boardPattern*2+1;
    delay(25);  
  }
  // Reverse empty
  for(int i=0; i<8; i++){
    shiftOut(boardPattern);
    boardPattern = boardPattern<<1;
    delay(25);  
  }
}

void shiftOut(byte pattern){
  // Byte with pattern: 10000000.
  // Will select the left most byte when anded with the pattern.
  // selectByte is then shifted one to the left and the process repeaten.
  byte selectByte = 128;
  
  for(int i=0; i<8; i++){
    // And select byte and pattern to see if current bit 
    // is high or low.
    if((selectByte&pattern) != 0){
      // Toggle data line high if bit is high.
      digitalWrite(data, HIGH);
    } else {
      // Toggle data line low if not.
      digitalWrite(data, LOW);
    }
    // Clock the bit
    digitalWrite(clk, HIGH);
    delay(1);
    digitalWrite(clk, LOW);
    delay(1);
    // Shift the select byte one to the left
    // Rememeber shift regs are MSB first.
    selectByte = selectByte>>1;
  }

  // Pull latch high one all bits has been shifed,
  digitalWrite(latch, HIGH);
  delay(1);
  digitalWrite(latch, LOW);
}

