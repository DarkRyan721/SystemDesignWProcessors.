#include <stdio.h>
int absdiff(int x, int y);

int main()
{
    printf("%d\n",absdiff(5,4));
}

int absdiff(int x, int y)
{
    return x > y ? x - y : y - x;
}
