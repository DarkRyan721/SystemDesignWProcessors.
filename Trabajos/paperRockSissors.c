#include <stdio.h>
char *AB[3][3] = {{"e", "B", "A"}, {"A", "e", "B"}, {"B", "A", "e"}};
int rockPaperScissor(int A, int B) { return printf("%s\n", AB[A][B]); }
int (*pointerTo)(int, int) = rockPaperScissor;
int main() { return pointerTo(1, 2); }

/*
#include <stdio.h>
void empate() {printf("empate");} void ganaA()  {printf("gana A");} void ganaB()  {printf("gana B");}
void (*AB[3][3])() = {{empate, ganaB, ganaA}, {ganaA, empate, ganaB}, {ganaB, ganaA, empate}};
int main(){*AB[1][1];}
*/

