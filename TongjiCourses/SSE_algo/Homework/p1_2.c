#include <stdio.h>

int convert_decimal_to_binary(int dec_number) {
    static char s[100];
    int length = 0;
    while(dec_number) {
        s[length++] = dec_number % 2;
        dec_number /= 2;
    }
    for(int i = -1 + length;i >= 0; --i)
    {
        // putchar(s[i]);
        printf("%d", s[i]);
    }
    putchar('\n');
    return 0;
}

int main() {
    printf("%d\n", convert_decimal_to_binary(17));
}
