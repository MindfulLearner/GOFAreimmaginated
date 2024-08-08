#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int cacciaPlayer;
} giocatore;
typedef struct {
    int cacciaComputer;
} computer;
typedef struct {
    int cacciaPlayer;
    int cacciaComputer;
} pianeta;


// STRUTTURA PLAYER RESET ANCHE PIANETA
giocatore player = {0};
// STRUTTURA PIANETA SESET
pianeta pianetaA = {0};

// BOOL
bool whileComandi = true;

const char *pianetiList[] = {
    "PIANETA-A",
    "PIANETA-B",
}; 

const char *arrayComando[] = {
    "HELP",
    "PRODUCINAVI",
    "MANDANAVI",
    "EXIT",
    "USCITATOTALE"
}; 

void computerAction() {
    for (int timer = 5; timer > 0; timer--) {
        sleep(1);
        printf("%d\n", timer);
    }
printf("ciao chiuso computer\n");
}

//mandaNavi funzioner
// AGGIUNGERE IF DI CONTROLLO SE PRESENTI SE POSSIBILE 
void mandaNavi(giocatore *player, pianeta *pianetaA){
    int naviDaMandare;
    static char nomeDelPianeta[50];
    printf("Quanti navi vuoi mandare?\n");
    scanf("%d", &naviDaMandare);
    printf("In che pianeta vuoi mandarli?\n");
    printf("Puoi inviarli in:\n");
    printf("PIANETA-A\n");
    printf("PIANETA-B\n");
    scanf("%49s", &nomeDelPianeta);
    // comparazione nome pianeta e pianeti list
    if (strcmp(nomeDelPianeta, pianetiList[0]) == 0){
        // meno a player + a pianeta selezionato
        // CONTROLLO NAVI FUNZIONANATE
        if (player->cacciaPlayer > naviDaMandare) {
            player->cacciaPlayer -= naviDaMandare;
            pianetaA -> cacciaPlayer += naviDaMandare; 
        } else {
            printf("non hai abbastanza navi da mandare\n");
        }
    }
};


// produci navi da mettere poi limite
void produciNavi(giocatore *player) {
    int nuoveNavi;
    printf("Quanti navi vuoi produrre?\n");
    scanf("%d", &nuoveNavi);
    player->cacciaPlayer += nuoveNavi;
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

// comandi di richiesta 
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
        // produci navi 
        printf("-------------------------------------------\n");
        printf("PRODUCINAVISWAG\n");
        produciNavi(&player);
        printf("-------------------------------------------\n");
    } else if (strcmp(inputUtente, arrayComando[2]) == 0) {
        printf("-------------------------------------------\n");
        printf("MANDANAVI\n");
        mandaNavi(&player, &pianetaA);
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

    printf("bot inizio programma, iniziera' mandare ogni 10 secondi 5 caccia in pianeta A\n");
    computerAction();

    while (whileComandi == true) { 
        char *inputUtente = bufferComandi(); 
        risposteComandi(inputUtente);
    }
    printf("Totalenavi: %d\n", player.cacciaPlayer);
    printf("Totale navi in pianeta a : %d\n", pianetaA.cacciaPlayer);
    return 0;
}

















