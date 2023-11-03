/* Ruler 1         2         3         4         5         6         7        */

// COMPILE WITH:          gcc emoji.c conio.c -o emoji

/* emoji.c ********************************************************************/
/*                                                                            */
/*   +----+ +----+                          BOUNCING EMOJI                    */
/*   ++  ++ ++******                                                          */
/*    |  |   |**  **      This is a simple example of using an animation      */
/*    |  |   | *  *       in ANSI C. This source code with main function      */
/*    |  |   | *  *       together with "conio" library can be easily         */
/*    |******| *  *       used to implement animation with a SINGLE instance  */
/*    |**  **| *  *                                                           */
/*    ++*  ** **  *       DOCUMENTED BY: Ing. Juan-Carlos Giraldo, Ph.D.      */
/*     +**  ***  **                      jcgiraldo@javeriana.edu.co           */
/*      +**     **                                                            */
/*        *******         Bogota, D.C., May 31th, 2023.                       */
/*                                                                            */
/*          Copyright (C) Department de Electronics                           */
/*                        School of Engineering                               */
/*                        Pontificia Universidad Javeriana                    */
/*                        Bogota - Colombia - South America                   */
/*                                                                            */
/******************************************************************************/

/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "conio.h"

/**************************** Definition of Emojis ****************************/

const char *happy[] = {
	"\U0001F600", /* 😀 */
	""};

const char *space_invader[] = {
	"\U0001F47E", /* 👾 */
	""};

const char *alien[] = {
	"\U0001F47D", /* 👽 */
	""};

const char *smiley[] = {
	"\U0001F604", /* 😄 */
	""};

const char *heart[] = {
	"\U00002764", /* ❤️ */
	""};

const char *star[] = {
	"\U00002B50", /* ⭐ */
	""};

const char *thumbs_up[] = {
	"\U0001F44D", /* 👍 */
	""};

const char *palm_tree[] = {
	"\U0001F334", /* 🌴 */
	""};

const char *cake[] = {
	"\U0001F370", /* 🍰 */
	""};

/******************* Prototype of Functions in Current File *******************/

void drawElement(const char *[], char, char);
void clearElement(const char *[], char, char);
void Frame(char, char, char, char);

/******************************* Main Function ********************************/

/*FN****************************************************************************
 *
 *   Purpose: Animate a single emoji through the screen
 *
 *   Plan:    Part 1: Clear object
 *            Part 2: Update state
 *            Part 3: Bounces if collided with a wall
 *            Part 4: Draw current object based on state
 *            Part 5: Freeze object in a given position
 *
 *   Register of Revisions:
 *
 *   DATE         RESPONSIBLE  COMMENT
 *   -----------------------------------------------------------------------
 *   Apr 20/2020  J.C.Giraldo  Initial implementation
 *
 *******************************************************************************/

unsigned char width = 2;
unsigned char height = 1;

unsigned char screenWidth;
unsigned char screenHeight;

// Define the codition initial for the display
void FillMatrix()
{
	Get_Console_Size(&screenWidth, &screenHeight);
	screenWidth = (screenWidth % 2 ? screenWidth - 1 : screenWidth);
	Clear_Screen();
	for (int j = 1; j <= screenHeight; j++)
		for (int i = 1; i <= screenWidth; i++)
			gotoxy(i, j), printf("\u253C");
}

// Emoji as an object to make different instances
typedef struct
{
	unsigned char positionX;
	unsigned char positionY;
	unsigned char deltaX;
	unsigned char deltaY;
	const char **type;
	float sleepTime;
} Emoji;

// Emoji constructor
Emoji createEmoji(const char **type, unsigned char positionX, unsigned char positionY, unsigned char deltaX, unsigned char deltaY, float sleepTime)
{
	Emoji newEmoji;
	newEmoji.type = type;
	newEmoji.positionX = positionX;
	newEmoji.positionY = positionY;
	newEmoji.deltaX = deltaX;
	newEmoji.deltaY = deltaY;
	newEmoji.sleepTime = sleepTime;
	return newEmoji;
}

// Emoji state with pointers to mantain the memory of instances
void EmojiState(Emoji *emoji)
{
	/* Part 1: Clear object */

	clearElement((emoji->type), emoji->positionX, emoji->positionY);

	/* Part 2: Update state */

	emoji->positionX = emoji->positionX + emoji->deltaX;
	emoji->positionY = emoji->positionY + emoji->deltaY;

	/* Part 3: Bounces if collided with a wall */

	if (!(emoji->positionX > 2 && emoji->positionX < screenWidth - width))
		emoji->deltaX = emoji->deltaX * -1;

	if (!(emoji->positionY > 2 && emoji->positionY < screenHeight - height))
		emoji->deltaY = emoji->deltaY * -1;

	/* Part 4: Draw current object based on state */

	drawElement(emoji->type, emoji->positionX, emoji->positionY);

	/* Part 5: Freeze object in a given position */

	// sleep(emoji->sleepTime);
}
int main()
{
	// Contexto generado.

	int tamEmojies = 20;
	Emoji arrayEmoji[tamEmojies];
	const char **emojiTypes[10] = {happy, alien, space_invader, smiley, heart, star, thumbs_up, palm_tree, cake, alien};
	srand(time(NULL));

	// Se incializa aleateriamente los valores de cada objeto.
	for (int i = 0; i < tamEmojies; i++)
	{
		arrayEmoji[i] = createEmoji(emojiTypes[(rand() % 10)],
									(rand() % screenWidth) + 1, (rand() % screenHeight) + 1,
									(rand() % 5) + 1, (rand() % 2) + 1,
									((float)rand() / RAND_MAX) * 1);
	}
	int i = 0;
	// Se realiza el estado inicial
	FillMatrix();

	Frame(1, 1, screenWidth, screenHeight);

	Cursor(0);

	// concurrent FSM
	while (1)
	{
		EmojiState(&arrayEmoji[i % 20]);
		i++;
	} /* while */

	return 0;

} /* main */

/******************* Definition of Functions in Current File ******************/

/*FN****************************************************************************
 *
 *   void drawElement( const char *element[], char x, char y );
 *
 *   Purpose: Draw an element previously defined in strings
 *
 *   Plan:    Simple function that does not need a plan description
 *
 *   Register of Revisions:
 *
 *   DATE         RESPONSIBLE  COMMENT
 *   -----------------------------------------------------------------------
 *   Apr 07/2023  J.C.Giraldo  Initial implementation
 *
 *******************************************************************************/

void drawElement(const char *element[], char x, char y)
{
	for (int i = 0, j = 0; element[i][0] != '\0'; i++, j++)
	{
		gotoxy(x, y + j);
		printf("%s\n", element[i]);
	}

} /* drawElement */

/*FN****************************************************************************
 *
 *   void clearElement( const char *element[], char x, char y );
 *
 *   Purpose: Draw an element previously drawn with UNICODE
 *
 *   Plan:    Simple function that does not need a plan description
 *
 *   Register of Revisions:
 *
 *   DATE         RESPONSIBLE  COMMENT
 *   -----------------------------------------------------------------------
 *   Apr 07/2023  J.C.Giraldo  Initial implementation
 *
 *******************************************************************************/

void clearElement(const char *element[], char x, char y)
{
	for (int i = 0, j = 0; element[i][0] != '\0'; i++, j++)
	{
		gotoxy(x, y + j);
		int width = strlen(element[0]) / 3;
		for (int spaces = 0; spaces < width; spaces++)
			printf(" ");
	}

} /* clearElement */

/*FN****************************************************************************
 *
 *   void Frame();
 *
 *   Purpose: Draw a frame with rounded corners
 *
 *   Register of Revisions (Debugging Process):
 *
 *   DATE       RESPONSIBLE  COMMENT
 *   -----------------------------------------------------------------------
 *   Oct 01/21  J.C.Giraldo  Initial implementation
 *
 *******************************************************************************/

void Frame(char x, char y, char dx, char dy)
{
	gotoxy(x, y);
	printf("\u256D");

	gotoxy(x + 1, y);
	for (int i = x + 1; i < x + dx - 1; i++)
		printf("\u2500");

	gotoxy(x + dx - 1, y);
	printf("\u256E");

	for (int j = y + 1; j < y + dy - 1; j++)
	{
		gotoxy(x, j);
		printf("\u2502");
	}

	for (int j = y + 1; j < y + dy - 1; j++)
	{
		gotoxy(x + dx - 1, j);
		printf("\u2502");
	}

	gotoxy(x, y + dy - 1);
	printf("\u2570");

	gotoxy(x + 1, y + dy - 1);
	for (int i = x + 1; i < x + dx - 1; i++)
		printf("\u2500");

	gotoxy(x + dx - 1, y + dy - 1);
	printf("\u256F");

} /* Frame */
