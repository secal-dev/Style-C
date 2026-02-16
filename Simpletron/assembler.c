//
// Created by Sebastiano Calabrò on 16/02/26.
//


#include <ctype.h>
#include <stdio.h>
#include <string.h>

//TABELLA DEI SIMBOLI

#define MAX_SYMBOLS 100     //massimo numero di simboli (100 word)
#define MAX_LINE 256        //massimo righe di istruzioni
#define MAX_LABEL 20        //massimo numero di caratteri per label
#define MAX_MEM 100         //massima memoria del simpletron

typedef struct {            //ogni istruzione ha una label e un indirizzo di memoria (es: move 20)
    char label[MAX_LABEL];
    int address;

}symbol_t;

symbol_t symbolTabel[MAX_SYMBOLS];

int symbols_counter = 0;

int  locationCounter = 0;

char startwithSemicolon(char *s) {          //se l'istruzione inizia con un ';' vado avanti
    while (isspace(*s)) ++s;
    if (*s == ';') return 1;
    else return 0;
}

void addSymbol(const char *label, int address) {            //funzione per aggiungere una label alla tabella dei simboli
    if (symbols_counter < MAX_SYMBOLS) {
        strcpy(symbolTabel[symbols_counter].label, label); //copia la label nella tabella
        symbolTabel[symbols_counter].address = address;    //associando l'indirizzo
        ++symbols_counter;                                 //incremento il puntatore
    }
}

void firstPass(FILE * input ) {     //prima passata del file di input
    char line[MAX_LINE];
    char linetoken[MAX_LINE];

    while (fgets(line, MAX_LINE, input) && locationCounter < MAX_MEM) {  //leggo il file con fgets
        line[strcspn(line, "\n")] = '\0';                           //pulisce "\n"

        if (strlen(line) == 0) continue;
        if (startwithSemicolon(line)) continue;

    strcpy(linetoken, line);        //poiche la strtok è distruttiva, conservo una copia della riga in una variabile che uso per estrapolare la label

    char* token = strtok(linetoken, " \t");

    if (token == NULL) continue;

    if (strchr(token, ':') != NULL) {   //LABEL TROVATA (caratteri prima di ':')
        int len = strlen(token);
        if (len > 0 && token[len-1] == ':') token[len-1] = '\0'; //elimino ':' dalla label
        addSymbol(token, locationCounter);                      //aggiungo la label alla tabella dei simboli

        token = strtok(NULL, " \t");                        //continuo a tokenizzare

    }
    if (token != NULL) {
        if (strcmp(token, "WORD") == 0){                        //se l'istruzione è WORD, ogni valore che segue occupa una cella di memoria (costante)
            while (strtok(NULL, " \t") != NULL) ++locationCounter;
        }
    }else {
        ++locationCounter;
    }

    }

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("mising argoument");
        return 1;
    } //se non riceve 2 parametri restituisce errore

    char inputfile[1024];
    char outputfile[1024];

    char listFile[100];

    strcpy(inputfile, argv[1]);

    char *a = strrchr(inputfile, '.');


    FILE *inputFP = fopen(inputfile, "r");

    if (!inputFP) {
        printf("Couldn't open inputfile");
        return -1;

    }
    firstPass(inputFP);

    for (int i = 0; i < symbols_counter; i++) {
        printf("%s\n%d\n", symbolTabel[i].label, symbolTabel[i].address);
    }

    return 0;
}
