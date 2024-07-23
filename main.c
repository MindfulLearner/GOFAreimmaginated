#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int cacciaPlayer;
} giocatore;
typedef struct {
    int cacciaPlayer;
} pianeta;




// STRUTTURA PLAYER
giocatore player = {0};



// BOOL
bool whileComandi = true;




// produci navi da mettere poi limite
void produciNavi(giocatore *giocatore) {
    int nuoveNavi;
    printf("Quanti navi vuoi produrre?\n");
    scanf("%d", &nuoveNavi);
    giocatore->cacciaPlayer += nuoveNavi;
}

const char *arrayComando[] = {
    "HELP",
    "PRODUCINAVI",
    "MANDANAVI",
    "EXIT",
        "USCITATOTALE"
}; 

char* bufferComandi() {
    bool booleanoComandi = true;
    static char comando[50];
    while (booleanoComandi) {
        printf("Inseriesci dei comandi, scrivi help se vuoi vedere la lista dei comandi: ");
        scanf("%49s", comando);
        for (int i = 0; i < sizeof(arrayComando)/sizeof(arrayComando[0]); i++) {
            if (strcmp(comando, arrayComando[i]) == 0){
                return comando;
            }
        }
        printf("Comando Errato riprova\n");
    }
}

bool risposteComandi(const char* inputUtente) {
    if (strcmp(inputUtente, arrayComando[0]) == 0) {
        printf("-------------------------------------------\n");
        printf("I comandi che hai a disposizione sono:\n");
        printf("'TUTORIAL' per vedere le istruzioni di gioco e come gicoare\n");
        printf("'PRODUCINAVI' per produrre navi\n");
        printf("'MANDANAVI' per mandare le navi ai pianeti\n");
        printf("'EXIT' per andare in Lobby Main\n");
        printf("'USCITATOTALE' per uscire totalemente\n");
        printf("-------------------------------------------\n");
    } else if (strcmp(inputUtente, arrayComando[1]) == 0) {
        printf("-------------------------------------------\n");
        printf("PRODUCINAVISWAG\n");
        produciNavi(&player);
        printf("-------------------------------------------\n");
    } else if (strcmp(inputUtente, arrayComando[2]) == 0) {
        printf("-------------------------------------------\n");
        printf("MANDANAVI\n");
        printf("-------------------------------------------\n");
    } else if (strcmp(inputUtente, arrayComando[3]) == 0) {
        printf("RITORNO A MAIN\n");
        return whileComandi = false;
    }
     else if (strcmp(inputUtente, arrayComando[4]) == 0) {
        printf("FINE PROGRAMMA..");
        exit(1);
    }

}

// inizio programma
int main () {


    // configurazione init a 0 di struct Giocatori
    // configuro la prompt comandi 
    // ----------------------------------------------------------------------------------------------
    // ------------------------------------PROMPTS COMMANDI GIOCO -----------------------------------
    // ----------------------------------------------------------------------------------------------
    
    while (whileComandi == true) { 
        char *inputUtente = bufferComandi(); 
        risposteComandi(inputUtente);
    }
    printf("Totalenavi: %d\n", player.cacciaPlayer);
    return 0;
}

















