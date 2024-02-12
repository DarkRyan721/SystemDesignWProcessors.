#define QT     0 /* QUIET */
#define E6  1319
#define G6  1568
#define A6  1760
#define AS6 1865
#define B6  1976
#define C7  2093
#define D7  2349
#define E7  2637
#define F7  2794
#define G7  3136
#define A7  3520 
int melodyPin = A5;  // Pin del buzzer 
  
typedef struct {
    unsigned int tone;   /* Tone [cycles per second: cps] */
    unsigned long length; /* Time for reproducing tone [milliseconds] */
} TONE_T;

TONE_T Super_Mario[] = {
    { E7, 80 },  { E7, 80 },  { QT, 80 },  { E7, 80 },
    { QT, 80 },  { C7, 80 },  { E7, 80 },  { QT, 80 },
    { G7, 80 },  { QT, 80 },  { QT, 80 },  { QT, 80 },
    { G6, 80 },  { QT, 80 },  { QT, 80 },  { QT, 80 },
    
    { C7, 80 },  { QT, 80 },  { QT, 80 },  { G6, 80 },
    { QT, 80 },  { QT, 80 },  { E6, 80 },  { QT, 80 },
    { QT, 80 },  { A6, 80 },  { QT, 80 },  { B6, 80 },
    { QT, 80 },  { AS6, 80 }, { A6, 80 },  { QT, 80 },
    
    { G6, 110 }, { E7, 110 }, { G7, 110 },
    { A7, 80 },  { QT, 80 },  { F7, 80 },  { G7, 80 },
    { QT, 80 },  { E7, 80 },  { QT, 80 },  { C7, 80 },
    { D7, 80 },  { B6, 80 },  { QT, 80 },  { QT, 80 },
    
    { C7, 80 },  { QT, 80 },  { QT, 80 },  { G6, 80 },
    { QT, 80 },  { QT, 80 },  { E6, 80 },  { QT, 80 },
    { QT, 80 },  { A6, 80 },  { QT, 80 },  { B6, 80 },
    { QT, 80 },  { AS6, 80 }, { A6, 80 },  { QT, 80 },
    
    { G6, 110 }, { E7, 110 }, { G7, 110 },
    { A7, 80 },  { QT, 80 },  { F7, 80 },  { G7, 80 },
    { QT, 80 },  { E7, 80 },  { QT, 80 },  { C7, 80 },
    { D7, 80 },  { B6, 80 },  { QT, 80 },  { QT, 80 }

};

unsigned int melodySize = sizeof(Super_Mario) / sizeof(TONE_T);
double melodyPause = 1.3;


int matrizPinesFilas[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int matrizPinesColumnas[8] = {10, 11, 12, 13, 14, 15, 16, 17};

const int buzzerPin = A4;
int ballsNumber = 4; 
struct Ball {
  int x;
  int y;
  int deltaX;
  int deltaY;
};

Ball balls[4]; // Un arreglo de 4 bolas

enum State {
  STATE_MOVE,
  STATE_BOUNCE
};

State currentStates[4] = {STATE_MOVE, STATE_MOVE, STATE_MOVE, STATE_MOVE};  // Estados iniciales para 4 bolas
unsigned long stateStartTimes[4] = {0, 0, 0, 0};  // Almacena los tiempos iniciales para cada bola
int ballDelay = 5;

int numRows = 8;
int numCols = 8;

void setup() {
   // Inicializa el buzzer
  pinMode(melodyPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  // Inicializa los pines de la matriz LED
  InitializeMatriz();
  InitializeBalls();
  
}

void loop() {
   
 bouncing_balls();
}



/*
++++++++++++++++++++++++++++++++ FUNCIONES+++++++++++++++++++++++++++++++++++++++++++++++++
*/
/*
+++++++++++++++++++++++++FUNCION PARA INICIALIZAR LAS BOLAS+++++++++++++++++++++++++++ 
*/

void bouncing_balls(){
  unsigned long currentTime = millis();
      static unsigned int noteIndex = 0;
      static unsigned long noteStartTime = 0;
      
      if (noteIndex >= melodySize) {
        noteIndex = 0;  // Reinicia la melodía al principio
      }
      else if (noteIndex < melodySize) {
        if (Super_Mario[noteIndex].tone != QT) {
          if (currentTime - noteStartTime >= Super_Mario[noteIndex].length) {
            noTone(melodyPin);
            noteStartTime = currentTime;
            noteIndex++;
          } 
          else {
            tone(melodyPin, Super_Mario[noteIndex].tone);
          }
        } 
        else {
          if (currentTime - noteStartTime >= Super_Mario[noteIndex].length) {
            noTone(melodyPin);
            noteStartTime = currentTime;
            noteIndex++;
          }
        }
    }
    

    displayBalls();

    for (int i = 0; i < 4; i++) {
      switch (currentStates[i]) {
        case STATE_MOVE:
          if (currentTime - stateStartTimes[i] >= ballDelay) {
            balls[i].x += balls[i].deltaX;
            balls[i].y += balls[i].deltaY;
            stateStartTimes[i] = currentTime;

          }
          evaluate_colissions(i);
          if (balls[i].x <= 0 || balls[i].x >= numCols - 1 || balls[i].y <= 0 || balls[i].y >= numRows - 1) {
            currentStates[i] = STATE_BOUNCE;
            stateStartTimes[i] = currentTime;
          }

          break;

        case STATE_BOUNCE:
          if (currentTime - stateStartTimes[i] >= ballDelay) {
            if (balls[i].x <= 0 || balls[i].x >= numCols - 1) {
              balls[i].deltaX = -balls[i].deltaX;
            }
            if (balls[i].y <= 0 || balls[i].y >= numRows - 1) {
              balls[i].deltaY = -balls[i].deltaY;
            }
            evaluate_colissions(i);
            currentStates[i] = STATE_MOVE;
            stateStartTimes[i] = currentTime;
          }
          break;   
      }
    }

    delay(50);
}

/*
+++++++++++++++++++++++++FUNCION PARA INICIALIZAR LAS BOLAS+++++++++++++++++++++++++++ 
*/
void InitializeBalls() {
  // Inicializa las bolas
  for (int i = 0; i < 4; i++) {
    balls[i].x = random(0, numCols);
    balls[i].y = random(0, numRows);
    balls[i].deltaX = random(1, 1.3);
    balls[i].deltaY = random(1, 1.3);
  }
}

/*
+++++++++++++++++++++++++FUNCION PARA INICIALIZAR LEDS MATRIZ+++++++++++++++++++++++++++ 
*/
void InitializeMatriz() {
 for (int i = 0; i < 8; i++) {
    pinMode(matrizPinesFilas[i], OUTPUT);
    pinMode(matrizPinesColumnas[i], OUTPUT);
  }
} 

/*
+++++++++++++++++++++++++FUNCION PARA  TOCAR MUSICA+++++++++++++++++++++++++++ CREADA POR ING. GIRALDO
*/
void PlayMelody(TONE_T *melody, unsigned int melodySize, double melodyPause) {
  for (unsigned int note = 0; note < melodySize; note++) {
    if (melody[note].tone != QT) {
      tone(melodyPin, melody[note].tone, melody[note].length);
    } else {
      delay(melody[note].length);
    }
    delay(melody[note].length * melodyPause);
  }
}
/*
+++++++++++++++++++++++++FUNCION PARA ENCENDER DISPLAY+++++++++++++++++++++++++++
*/
void displayBalls() {
  // Apaga todos los LEDs
  apagarDisplay();
    // Enciende los LEDs en las posiciones de las bolas:

  for (int i = 0; i < 8; i++) { //BARRIDO DE FILAS
    //digitalWrite(matrizPinesFilas[i], HIGH);
    for (int ball = 0; ball < 4; ball++){ // RECORRE LA STRUCT DE BOLAS (4)

        if (balls[ball].x == i){ //PREGUNTO SI la POSX de la bola coincide con la fila
          digitalWrite(matrizPinesFilas[i], LOW);
          for (int cols = 0; cols < 8; cols++) { //BARRIDO DE COLUMNAS

            if (balls[ball].y == cols){//PREGUNTO SI la POSY de la bola( que esta en la fila de coincidencia) coincide con la comlumna
            
              digitalWrite(matrizPinesColumnas[cols], HIGH);
            }
          }
        }

    }
    apagarDisplay();
    //digitalWrite(matrizPinesFilas[i], HIGH);
  }

}
/*
+++++++++++++++++++++++++FUNCION PARA APAGAR DISPLAY+++++++++++++++++++++++++++
*/
void apagarDisplay(){
   // Apaga todos los LEDs
  for (int row = 0; row < numRows; row++) {
    digitalWrite(matrizPinesFilas[row], HIGH);
    for (int col = 0; col < numCols; col++) {
      digitalWrite(matrizPinesColumnas[col], LOW);
    }
  }
}


/*
+++++++++++++++++++++++++FUNCION PARA EVALUAR COLISIONES DISPLAY+++++++++++++++++++++++++++
*/
void evaluate_colissions(int pelota){

    for (int j = 1 ; j <= 4; j++) {
      if (pelota == j){
        continue;
      }
      if (balls[pelota].x == balls[j].x && balls[pelota].y == balls[j].y){
        //BOLA QUE SE CHOCO
        tone(buzzerPin, 440, 100);
        balls[pelota].deltaX = -balls[pelota].deltaX;
        balls[pelota].deltaY = -balls[pelota].deltaY;
        //BOLA CON LA QUE SE CHOCO
        balls[j].deltaX = -balls[j].deltaX;
        balls[j].deltaY = -balls[j].deltaY;

      }
    }
}