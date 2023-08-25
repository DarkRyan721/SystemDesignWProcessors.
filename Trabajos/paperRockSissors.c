#include <stdio.h>
char *AB[3][3] = {{"e", "B", "A"}, {"A", "e", "B"}, {"B", "A", "e"}};
int rockPaperScissor(int A, int B) { return printf("%s\n", AB[A][B]); }
int (*pointerTo)(int, int) = rockPaperScissor;
int main() { return pointerTo(1, 2); }
