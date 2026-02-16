//Sebastiano Calabro 02/2026

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRTOI -> STRING TO INT

int atoi1 (char s[]) { //ATOI -> ASCII to INT : converte da stringa a intero (stdlib)
    int n = 0;

    for (int i = 0;  s[i] >= '0' && s[i] <= '9'; i++) {

        n = n * 10;
        n += s[i] - '0';
    }

    return n;

}

int* resize (int *a, int i) { //aumenta dinamicamente la dimensione dell'array
    int *b = realloc(a, (i+1) * sizeof(int));

    return b;

}

int* strtoi(char *stringa, const char *separator) {
    //String to array di integer

    int *a = NULL;
    int i = 0;

    char *tok = strtok(stringa, separator);
    //Strtok = tokenizza la stringa con un separatore -> restituisce il puntatore alla prima occorrenza, memorizzandolo per le chiamate succesive


    while (tok != NULL) {
        int *nuovo = resize(a, i);

        a = nuovo;

        a[i] = atoi1(tok);

        i++;

        tok = strtok(NULL, separator); //Chimata successiva solo con il separatore (puntatore alla stringa memorizzato nel buffer)

    }

    for (int h = 0; h < i; h++) {
        printf("%d\n", a[h]);
    }
    return a;
}


//FINE STRTOI


int main(int argc, char *argv[]) {

    char *stringa = argv[1];

    int *a = strtoi(stringa, ".");



    return 0;
}