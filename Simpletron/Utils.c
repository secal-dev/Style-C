//Sebastiano Calabro 02/2026

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRTOI -> STRING TO INT

int atoi1 (char s[]) {
    int n = 0;

    for (int i = 0;  s[i] >= '0' && s[i] <= '9'; i++) {

        n = n * 10;
        n += s[i] - '0';
    }

    return n;

}

int* resize (int *a, int i) {
    int *b = realloc(a, (i+1) * sizeof(int));

    return b;

}

int* strtoi(char *stringa, const char *separator) {

    int *a = NULL;
    int i = 1;

    char *tok = strtok(stringa, separator);


    while (tok != NULL) {
        int *nuovo = resize(a, i);

        a = nuovo;

        a[i] = atoi1(tok);

        i++;

        tok = strtok(NULL, separator);

    }

    a = resize(a, i);

    for (int h = 1; h == i; h++) {
        a[h] = a[h+1];
    }
    a[0] = i;

    return a;

}

void printarray_token(int * a) {
    for (int i = 0; i < a[0]; i++) {
        printf("%d\n", a[i]);
    }

}


int main(int argc, char *argv[]) {
    /*
    char *stringa = argv[1];
    int *a = strtoi(stringa, ".");

    printarray_token(a);
*/

    return 0;
}