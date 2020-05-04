//www.elegoo.com
//2016.12.12

int latch=A1;  //74HC595  pin 9 STCP
int clock_=9; //74HC595  pin 10 SHCP
int data=12;   //74HC595  pin 8 DS

unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};
//byte table[]=
//{
//0x3f, // 0011 1111 // 0
//0x06, // 0000 0110 // 1
//0x5b, // 0101 1011 // 2
//0x4f, // 0100 1111 // 3
//0x66, // 0110 0110 // 4
//0x6d, // 0110 1101 // 5
//0x7d, // 0111 1101 // 6
//0x07, // 0000 0111 // 7
//0x7f, // 0111 1111 // 8
//0x6f, // 0110 1111 // 9
//0x77, // 0111 0111 // A
//0x7c, // 0111 1100 // B
//0x39, // 0011 1001 // C
//0x5e, // 0101 1110 // D
//0x79, // 0111 1001 // E
//0x71, // 0111 0001 // F
//0x00  // 0000 0000 // 
//};

const byte TABLE2[] = {
  0xfc,
  0x60,
  0xda,
  0xf2,
  0x66,
  0xb6,
  0xbe,
  0xe2,
  0xfe,
  0xe6,
  0x0b,
  0xbd,
  0x3f
};
const byte R = 0x0b;
const byte G = 0xbd;
const byte B = 0x3f;

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock_,OUTPUT);
  pinMode(data,OUTPUT);
//  pinMode(11, OUTPUT);
  
  //digitalWrite(11, HIGH);
  
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(4, INPUT);
  pinMode(7, INPUT);

  digitalWrite(
    
  
}

void Display(unsigned char num)
{
  digitalWrite(latch,LOW);
  shiftOut(data,clock_,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);
}

void Display2(byte num)
{
  digitalWrite(latch,LOW);
  shiftOut(data,clock_,LSBFIRST,num);
  digitalWrite(latch,HIGH);
}

void loop() {
  for (int i = 0; i < 10; i++) {
    Display2(i);
    delay(700);
  }

//  Display(0x03);
//  Display2(0x02);

}
