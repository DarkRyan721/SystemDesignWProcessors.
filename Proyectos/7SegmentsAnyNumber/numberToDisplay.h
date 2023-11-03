#define D1 A1
#define D2 A2
#define D3 A3
#define D4 A4

#define a 5
#define b 6
#define c 7
#define d 8
#define e 9
#define f 10
#define g 11
#define dp 12

#define read 13

#define pwmPin 3
#define switchOutput 2
#define confirmationPin 1

static int n = 0; 

static int CurrentReferenceLevel1 = 0;
int timePersistence = 1;

static unsigned long cTime, pTime;

static unsigned long T = 0;

void clearLEDs() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
void zero() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}
void one() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
void two() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
void three() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
void four() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void five() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void six() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void seven() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
void eight() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void nine() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void pickDigit(int x) {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  switch (x) {
    case 0: digitalWrite(D1, LOW); break;
    case 1: digitalWrite(D2, LOW); break;
    case 2: digitalWrite(D3, LOW); break;
    case 3: digitalWrite(D4, LOW); break;
  }
}
void pickNumber(int x) {
  switch (x) {
    default: zero(); break;
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
  }
}
int delayMine(int time) {
  static unsigned long current = millis();
  static unsigned long previous = millis();
  if (current - previous <= time) {
    current = millis();
    return 0;
  } else {
    current = previous = millis();
    return 1;
  }
}


void numberToDisplay(int number) {
  number = number > 9999 ? 9999 : number;
  number = number < 0 ? 0 : number;
  
  clearLEDs();
  pickDigit(3);
  pickNumber((number) % 10);
  delay(1);
  clearLEDs();
  pickDigit(2);
  pickNumber((number /= 10) % 10);
  delay(1);
  clearLEDs();
  pickDigit(1);
  pickNumber((number /= 10) % 10);
  delay(1);
  clearLEDs();
  pickDigit(0);
  pickNumber((number /= 10) % 10);
  delay(1);
}