//SML -> Simpletron Machine Language



#include <stdio.h>

#define MEM_SIZE 100 //definisco la dimensione di default della memoria del calcolatore

#define MAX_LEN 6   //massima lunghezza delle istruzioni del calcolatore + \n + terminatore di stringa (es: 1020\n)
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40       //salto non condizionato
#define BRANCHNEG 41    //salto con <
#define BRANCHZERO 42   // salto con = 0
#define HALT 43


void dump(const int* const m, int a, unsigned int ic, int ir) {
    //printf("REGISTRI\n\n");
    printf("ACC \t\t%+05d\n", a);
    printf("INSCOUNT %d\n", ic);
    printf("INSREG %d\n", ir);

    for (int i = 0; i < MEM_SIZE; i += 10) {
        printf("%d\t%+05d\t%+05d\t%+05d\t%+05d\t%+05d\t%+05d\t%+05d\t%+05d\t%+05d\t%+05d\t\n", i, m[i], m[i+1],m[i+2],m[i+3],m[i+4],m[i+5],m[i+6],m[i+7],m[i+8],m[i+9]);

    }
    printf("finito\n");
}

void load_program(const char* filename, int* const m) {
    const FILE* fp = fopen(filename, "r");  //fopen restituisce una struct di tipo FILE: 1(File Descriptor), 2(Buffer), 3(Puntatori di posizione)

    if (fp == NULL) {printf("File mancante\n"); return;}

    unsigned int smem = 0;

    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, fp) != NULL){       //fgets bufferizza riga per riga partendo dal pointer di fp (fino a \n-/0) e la mette in nella stringa buffer[]
        sscanf(buffer, "%d", &m[smem++]);          //sscanf legge la stringa buffer e cerca un intero ("%d") e lo mette nella posizione corrente di m[spaziodimemoria]
    }
    fclose(fp);
}

int execute(int* const mem, int *accumulator, int* instruction_counter, int* instruction_register) {

    //*accumulator =+ 1;
    *instruction_register = mem[*instruction_counter];      //Instruction register indica l'istruzione corrente
    unsigned int opcode =mem[*instruction_counter] / 100;   //opcode sono le prime due cifre del comando che identificano l'istruzione
    unsigned int operand = mem[*instruction_counter] % 100; //l'operando è la destinazione dell'operazione dell'opcode

    switch(opcode) {
        case READ:          //l'istruzione READ (10) prende una variabile in input(dal buffer di STDIO) e la scrive nella cella di memoria 20(mem[operando])
            printf("Attesa di input\n");
            scanf("%d",&mem[operand]);
            ++(*instruction_counter);
            break;
        case WRITE:         //WRITE (11xx) accede ad una zona di memoria(xx) e lo scrive nel buffer di stream di I/O
            printf("%d\n\n", mem[operand]);
            ++(*instruction_counter);
            break;
        case LOAD:          //LOAD (20xx) carica il valore della memoria(xx) all'accumulatore
            *accumulator = mem[operand];
            printf("LOAD eseguita, accumulatore: %d\n", *accumulator);
            ++(*instruction_counter);
            break;
        case STORE:         //STORE (21xx) carica alla memoria(xx) il valore dell'accumulatore
            mem[operand] = *accumulator;
            printf("STORE eseguita, %d\n", mem[operand]);
            ++(*instruction_counter);
            break;
        case ADD:           //ADD (30xx) somma all'accumulatore il valore della memoria(xx)
            *accumulator += mem[operand];
            printf("ADD eseguita, accumulatore:%d\n", *accumulator);
            ++(*instruction_counter);
            break;
        case SUBTRACT:      //SUBTRACT (31xx) sottrae all'accumulatore il valore della memoria(xx)
            *accumulator -= mem[operand];
            printf("SUB eseguita, accumulatore: %d\n", *accumulator);
            ++(*instruction_counter);
            break;
        case DIVIDE:        //DIVIDE (32xx) divide all'accumulatore il valore della memoria(xx)
            *accumulator /= mem[operand];
            printf("DIV eseguita, accumulatore: %d", *accumulator);
            ++(*instruction_counter);
            break;
        case MULTIPLY:      //MULTIPLY (32xx) moltiplica all'accumulatore il valore della memoria(xx)
            *accumulator *= mem[operand];
            printf("MUL eseguita, accumulatore: %d\n", *accumulator);
            ++(*instruction_counter);
            break;
        case BRANCH:        //BRANCH (40xx) salta all'istruzione operand(xx)
            *instruction_counter = operand;
            printf("BRA eseguito, ir: %d\n", *instruction_counter);
            break;
        case BRANCHNEG:     //BRANCHNEG (41xx) salta all'istruzione xx solo se l'accumulatore < 0
            if (*accumulator < 0) {
                *instruction_counter = operand;
                printf("BRN eseguito, ir : %d\n", *instruction_counter);
            } else ++(*instruction_counter);    //Altrimenti prosegue con l'esecuzione incrementando il valore in instruction counter
            break;
        case BRANCHZERO:    //BRANCHZERO (42xx) salta all'istruzione xx solo se l'accumulatore == 0
            if (*accumulator == 0) {
                *instruction_counter = operand;
                printf("BRZ eseguito, ir: %d\n", *instruction_counter);
            } else ++(*instruction_counter); //Altrimenti prosegue con l'esecuzione incrementando il valore in instruction counter
            break;
        case HALT:          //HALT (4300) ferma l'esecuzione della funzione
            return 0;
    }
    return 1;
}

int main(){

    int mem[MEM_SIZE] = {0}; //alloco la memoria del calcolatore

    int accumulator = 0;
    unsigned int instruction_counter = 0; //indirizzo di memoria della prossima istruzione da eseguire (%RIP)
    int instrucion_register = 0; //FETCHING = preleva il valore della cella istruction_counter e lo  mette in (%IR)
    //queste 3 variabili sonsso il funzionamento base della cpu moderna: ad ogni clock aggiorna il valore dei tre

    printf("Welcome to Simpletron \n\n");


    load_program("somma", mem);


    //dump(mem, accumulator, instruction_counter, instrucion_register); //DUMP è una funzione che serve a visualizzare interamente lo stato del calcolatore

    while (execute(mem, &accumulator, &instruction_counter, &instrucion_register));

    printf("\n");
    dump(mem, accumulator, instruction_counter, instrucion_register); //visualizzo lo stato del calcolatore dopo l'esecuzione

    return 0;

ddawd
}