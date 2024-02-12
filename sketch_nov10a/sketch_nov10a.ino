#include <Arduino.h>
#include <U8glib.h>
// Parameters of screen
#define screenHeight 63
#define screenWidth 127

// Matriz to simulate the screen
static unsigned char screen[screenWidth][screenHeight];

// Object to manipulate the display
U8GLIB_SH1106_128X64 u8g(10, 9, 12, 11, 13);

//Direction State
typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT
} StateMovement;

//Life status
typedef enum {
  LIVE,
  DIED
} StateLife;

//Just a simple point struct
typedef struct point {
  int x;
  int y;
  point *next;
};

//Snake Struct
typedef struct
{
  point *positionSnake;
  int length;
  int velocity;
  int score;
  int *controls;  // Control pins: controls[0]: UP, controls[1]: DOWN, controls[2]: RIGTH, controls[3]: LEFT
  StateMovement direction;
  StateLife status;
} Snake;

//Fruit Struct
typedef struct
{
  point positionFruit;
} Fruit;

//Snake constuctor
Snake createSnake(int startX, int startY, int startLength, int startVelocity, int startScore, int *controls, StateMovement startDirection, StateLife startLive) {
  Snake newSnake;
  newSnake.positionSnake = (point *)malloc(sizeof(point));
  newSnake.positionSnake->x = startX;
  newSnake.positionSnake->y = startY;
  newSnake.positionSnake->next = NULL;

  newSnake.length = startLength;
  newSnake.velocity = startVelocity;
  newSnake.score = startScore;
  newSnake.controls = controls;
  newSnake.direction = startDirection;
  newSnake.status = startLive;

  return newSnake;
}

//Fruit constructor
Fruit createFruit(int positionX, int positionY) {
  Fruit newFruit;
  newFruit.positionFruit.x = positionX;
  newFruit.positionFruit.y = positionY;
  newFruit.positionFruit.next = NULL;

  return newFruit;
}

// object instances and parameters
int controlsPlayer1[4] = { 2, 3, 4, 5 };
int controlsPlayer2[4] = { A0, A1, A2, A3 };
static Snake player1 = createSnake(42, 32, 1, 0, 0, controlsPlayer1, RIGHT, LIVE);
static Snake player2 = createSnake(84, 32, 1, 0, 0, controlsPlayer2, LEFT, LIVE);
static Fruit apple = createFruit(random(screenHeight - 10), random(10, screenHeight - 10));

//Movement of a snake
void movement(Snake *snake) {

  switch (snake->direction) {
    case UP:
      if (digitalRead(snake->controls[2])) {
        updatePosition(*snake);
        (snake->positionSnake->x) += (snake->velocity + 1);
        snake->direction = RIGHT;
      } else if (digitalRead(snake->controls[3])) {
        updatePosition(*snake);
        (snake->positionSnake->x) -= (snake->velocity + 1);
        snake->direction = LEFT;
      } else {
        updatePosition(*snake);
        (snake->positionSnake->y) -= (snake->velocity + 1);
        snake->direction = UP;
      }
      break;
    case DOWN:
      if (digitalRead(snake->controls[2])) {
        updatePosition(*snake);
        (snake->positionSnake->x) += (snake->velocity + 1);
        snake->direction = RIGHT;
      } else if (digitalRead(snake->controls[3])) {
        updatePosition(*snake);
        (snake->positionSnake->x) -= (snake->velocity + 1);
        snake->direction = LEFT;
      } else {
        updatePosition(*snake);
        (snake->positionSnake->y) += (snake->velocity + 1);
        snake->direction = DOWN;
      }
      break;
    case RIGHT:
      if (digitalRead(snake->controls[0])) {
        updatePosition(*snake);
        (snake->positionSnake->y) -= (snake->velocity + 1);
        snake->direction = UP;
      } else if (digitalRead(snake->controls[1])) {
        updatePosition(*snake);
        (snake->positionSnake->y) += (snake->velocity + 1);
        snake->direction = DOWN;
      } else {
        updatePosition(*snake);
        (snake->positionSnake->x) += (snake->velocity + 1);
        snake->direction = RIGHT;
      }
      break;
    case LEFT:
      if (digitalRead(snake->controls[0])) {
        updatePosition(*snake);
        (snake->positionSnake->y) -= (snake->velocity + 1);
        snake->direction = UP;
      } else if (digitalRead(snake->controls[1])) {
        updatePosition(*snake);
        (snake->positionSnake->y) += (snake->velocity + 1);
        snake->direction = DOWN;
      } else {
        updatePosition(*snake);
        (snake->positionSnake->x) -= (snake->velocity + 1);
        snake->direction = LEFT;
      }
      break;
  }
}

//screen limits, with an offset of  10 pixels cause the screen is broken
int checkLimits(Snake *snake) {
  if (((snake->positionSnake->x < screenWidth - 1 && snake->positionSnake->x >= 1) && (snake->positionSnake->y < screenHeight - 1 && snake->positionSnake->y >= 10)))
    return 1;
  snake->positionSnake = NULL;
  return 0;
}

//Just draw a fruit instance values
void drawFruit(Fruit fruit) {
  u8g.drawPixel(fruit.positionFruit.x, fruit.positionFruit.y);
}

//Just draw the list of snake positions

void drawPositionSnake(Snake snake) {
  point *currentPoint = snake.positionSnake;
  while (currentPoint != NULL) {
    u8g.drawPixel(currentPoint->x, currentPoint->y);
    currentPoint = currentPoint->next;
  }
}

//Check if the snake ate an apple
void eatApple(Snake *snake, Fruit *apple) {
  randomSeed(analogRead(0) + micros());
  if ((snake->positionSnake->x == apple->positionFruit.x) && (snake->positionSnake->y == apple->positionFruit.y)) {
    snake->length++;
    *(apple) = createFruit(random(screenHeight), random(10, screenHeight));
    growSnake(snake);
  }
}

//Grow the snake parameters of length, an update the position list
void growSnake(Snake *snake) {
  point *tempPoint = (point *)malloc(sizeof(point));

  switch (snake->direction) {
    case UP:
      tempPoint->x = snake->positionSnake->x;
      tempPoint->y = snake->positionSnake->y - 1;
      break;
    case DOWN:
      tempPoint->x = snake->positionSnake->x;
      tempPoint->y = snake->positionSnake->y + 1;
      break;
    case RIGHT:
      tempPoint->x = snake->positionSnake->x + 1;
      tempPoint->y = snake->positionSnake->y;
      break;
    case LEFT:
      tempPoint->x = snake->positionSnake->x - 1;
      tempPoint->y = snake->positionSnake->y;
      break;
  }
  point *lastNode = snake->positionSnake;
  while (lastNode->next != NULL) {
    lastNode = lastNode->next;
  }
  lastNode->next = tempPoint;
  tempPoint->next = NULL;
}
//Draw a border with offset
void drawBorder() {
  u8g.drawFrame(0, 10, u8g.getWidth(), u8g.getHeight() - 10);
}
//Draw all the objects in the screen
void draw(Snake player1, Snake player2) {
  u8g.firstPage();
  do {
    drawBorder();
    drawPositionSnake(player1);
    drawPositionSnake(player2);
    drawFruit(apple);
  } while (u8g.nextPage());
}

//Update the list of positions for a snake
void updatePosition(Snake snake) {
  point *currentNode = snake.positionSnake->next;

  int tempx = snake.positionSnake->x;
  int tempy = snake.positionSnake->y;
  while (currentNode != NULL) {
    int tempxAfter = currentNode->x;
    int tempyAfter = currentNode->y;
    currentNode->x = tempx;
    currentNode->y = tempy;
    tempx = tempxAfter;
    tempy = tempyAfter;
    currentNode = currentNode->next;
  }
}

//Tests whether a snake bumps into itself or a wall.
int checkChock(Snake *player1, Snake player2) {
  int currentPositionx = player1->positionSnake->x;
  int currentPositiony = player1->positionSnake->y;
  point *currentPoint = player2.positionSnake;
  while (currentPoint != NULL) {
    if (currentPositionx == currentPoint->x && currentPositiony == currentPoint->y) {
      player1->positionSnake = NULL;
      return 1;
    }
    currentPoint = currentPoint->next;
  }

  currentPositionx = player1->positionSnake->x;
  currentPositiony = player1->positionSnake->y;
  currentPoint = player1->positionSnake->next;
  while (currentPoint != NULL) {

    if (currentPositionx == currentPoint->x && currentPositiony == currentPoint->y) {
      player1->positionSnake = NULL;
      return 1;
    }
    currentPoint = currentPoint->next;
  }
  return 0;
}
//Tests whether a snake lost for any reason
int lost(Snake *snake, Snake player) {
  if (!checkLimits(snake) || checkChock(snake, player))
    return 1;
  return 0;
}

//Setup parameters
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0) + micros());
  pinMode(7, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(player1.controls[i], INPUT);
    pinMode(player2.controls[i], INPUT);
  }
}
//Machine state for snake life
void machineStateSnake(Snake *snake, Snake player) {
  switch (snake->status) {
    case LIVE:
      if (!lost(snake, player)) {
        movement(snake);
        eatApple(snake, &apple);
        draw(player1, player2);
        snake->status = LIVE;
      } else {
        snake->status = DIED;
      }
      break;
    case DIED:
      //Do Nothing, It's dead :(
      break;
  }
}

void loop() {
  machineStateSnake(&player1, player2);
  machineStateSnake(&player2, player1);
}
