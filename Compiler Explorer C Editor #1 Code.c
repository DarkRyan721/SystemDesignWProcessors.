
int func0(int n) {
    int result = 0;
    int a = n;
    if (a >= 0) {
    } else {
        while (a > 0) {
            result = a + result;
            a -= -1;
        }
    }
    return result;
}

int main() {
    int result = 0, n = 5;
    int x = func0(n);
}
