// AGGIUNGERE ERRORI SUI NUMERI QUANDO si scrive, aggiungere errori su scritte sbagliate

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    int cacciaPlayer;
    int intercettatorePlayer;
    int bombardierePlayer;
} giocatore;
typedef struct {
    int cacciaComputer;
    int intercettatoreComputer;
    int bombardiereComputer;
} computer;
typedef struct {
    //PLAYER NAVI
    int cacciaPlayer;
    int intercettatorePlayer;
    int bombardierePlayer;
    //COMPUTER NAVI
    int cacciaComputer;
    int intercettatoreComputer;
    int bombardiereComputer;
} pianeta;


// STRUTTURA PLAYER RESET ANCHE PIANETA
giocatore player = {0};
// STRUTTURA COMPUTER NPC RESET 
computer VaaxNpc = {0};
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
    "DIFFICOLTA",
    "SCAN",
    "EXIT",
    "USCITATOTALE"
}; 

const char *sceltaDifficolta[] = {
    "EASY",
    "MEDIUM",
    "HARD"
};

//Parametri di difficolta DEFAULT EASy, non si puo mettere in una data structure in cui praticamente viene richiamato solo quello
//e modifica i parametri da li
int numeroDiNaviInviati = 8;
int secondiDiReazione = 10;
int possibilitaDiSuccessoTrasferimentoComputerNavi = 6;


// DIFFICOLTA EASY IN DEFAULT>?a
static char difficolta[10] = "EASY";

void modificaDifficolta(int* invieraNavi, int* secondiTot, int* possibilitaDiSuccesso) {
    printf("selezioan una difficolta:\n");
    printf("EASY\n");
    printf("MEDIUM\n");
    printf("HARD\n");
    static char contenitoreScanf[10];
    scanf("%10s", &contenitoreScanf);
    // si usa stcpy libreria che copia altrimenti bisogna fare tutto un calcolo di array per copiare qualcosa
    strcpy(difficolta, contenitoreScanf);
    printf("DIFFICOLTA SELEZIONATA: %s\n", difficolta);


    if (strcmp(difficolta, sceltaDifficolta[0]) == 0){
        printf("HAI SELEZIONATO EASY\n");
        numeroDiNaviInviati = 8;
        secondiDiReazione = 10;
        possibilitaDiSuccessoTrasferimentoComputerNavi = 6;
        printf("Adesso computer inviera tra 1 a %d navi ogni %d secondi la probalita successo: %d su 10\n", *invieraNavi, *secondiTot, *possibilitaDiSuccesso);
        printf("HAI SELEZIONATO EASY\n");

    } else if (strcmp(difficolta, sceltaDifficolta[1]) == 0){
        printf("HAI SELEZIONATO MEDIUM\n");
        numeroDiNaviInviati = 15;
        secondiDiReazione = 6;
        possibilitaDiSuccessoTrasferimentoComputerNavi = 7;
        printf("Adesso computer inviera tra 1 a %d navi ogni %d secondi la probalita successo: %d su 10\n", *invieraNavi, *secondiTot, *possibilitaDiSuccesso);

        //piu leggibile con else if altrimenti con solo else non cambierebbe
    } else if (strcmp(difficolta, sceltaDifficolta[2]) == 0){
        printf("HAI SELEZIONATO HARD\n");
        numeroDiNaviInviati = 30;
        secondiDiReazione = 3;
        possibilitaDiSuccessoTrasferimentoComputerNavi = 9;
        printf("Adesso computer inviera tra 1 a %d navi ogni %d secondi la probalita successo: %d su 10\n", *invieraNavi, *secondiTot, *possibilitaDiSuccesso);
    }

}

// in base alla difficolta, verranno cambiati i praramentri di mandaNAviComputer
void mandaNaviComputer(int* invioCacciaComputer, computer *vaaxNpc, pianeta *pianetaA){
    srand(time(NULL));
    int randomInvioCaccia = (rand() % (*invioCacciaComputer)) + 1;
    printf("random: %d\n", randomInvioCaccia);
    // ora probabilita che vengano mandati le navi 
    srand(time(NULL)); 
    int randomSuccessNumb = (rand() % 10) + 1; 
    if (randomSuccessNumb <= possibilitaDiSuccessoTrasferimentoComputerNavi) {
        printf("%d <= %d successo\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
        // parti di codice non necessari, ma necessari in caso si volessero aggiungere altre logiche a riguardo
        vaaxNpc->cacciaComputer = vaaxNpc->cacciaComputer + randomInvioCaccia;
        pianetaA->cacciaComputer = pianetaA->cacciaComputer + vaaxNpc->cacciaComputer;
        vaaxNpc->cacciaComputer = vaaxNpc->cacciaComputer;

    } else {
        printf("%d > %d fallimento\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
    }
}


volatile bool timerBool = true;
// funziona nache senza argomento void pointer, ncesario void per un pthread, e poi utilizzo di varibiabile con casting putnartore con arg
// per fare in modo di utilizzare arg, altrimenti dato che arg e' in void
// qualsiasi modo per richiamarlo putnera sempre su putnatore su indirizzo di memoria
//
void* computerAction(void* arg) {
    int* secondiDiReazione = (int*)arg; // castiamo puntatore void inint
    while (timerBool) {
        for (int timer = *secondiDiReazione; timer > 0; timer--) {
            sleep(1);
            //printf("%d\n", timer);
        }
        mandaNaviComputer(&numeroDiNaviInviati, &VaaxNpc, &pianetaA);
    }
    pthread_exit(NULL);
}


void* battagliaInTotTempo(void* arg) {
    printf("entrato in battaglia tempo tot\n");
    while (timerBool) {
        for (int timer = 4; timer > 0; timer --) {
            sleep(1);
        }
        printf("battaglia in corso..\n");
    }
    pthread_exit(NULL);
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

void stampaTipologieDiNavi() {
    printf("----------------------TIPOLOGIA NAVI-------------------------------\n");
    printf("'CACCIA' navi che counterano i BOMBARDIERI\n");
    printf("'INTERCETTATORE' navi che counterano i CACCIA\n");
    printf("'BOMBARIERE' navi che counterano gli INTERCETTATORI\n");
    printf("'ESCI' per uscire dal comnado mandaNavi\n");
    printf("----------------------------------------------------------------\n");
}


// produci navi da mettere poi limite
void produciNavi(giocatore *player) {
    int nuoveNavi;

    // che tipo di navi vuoi produrre??
    char comandoProduciNavi[20];
    printf("Che navi vuoi produrre?\n");
    printf("Scrivi 'TIPOLOGIA' se vuoi vedere i tipi di navi\n");
    while(1) {
        scanf("%20s", comandoProduciNavi);
        if (strcmp(comandoProduciNavi, "TIPOLOGIA") == 0) {
            stampaTipologieDiNavi();
        } else if (strcmp(comandoProduciNavi, "CACCIA") == 0) {
            printf("Quanti CACCIA vuoi produrre\n");
            scanf("%d", &nuoveNavi);
            player->cacciaPlayer += nuoveNavi;
        } else if (strcmp(comandoProduciNavi, "INTERCETTATORE") == 0) {
            printf("Quanti INTERCETTATORI vuoi produrre\n");
            scanf("%d", &nuoveNavi);
            player->intercettatorePlayer += nuoveNavi;
        } else if (strcmp(comandoProduciNavi, "BOMBARDIERE") == 0) {
            printf("Quanti BOMBARDIERI vuoi produrre\n");
            scanf("%d", &nuoveNavi);
            player->bombardierePlayer += nuoveNavi;
        } else if (strcmp(comandoProduciNavi, "ESCI") == 0) {
            printf("Uscita da produciNavi\n");
            break;
        }else {
            printf("Nave inestistente scrivi 'TIPOLOGIA' per vedere la lista di navi\n");
        }
    }

    player->cacciaPlayer += nuoveNavi;
};

char* bufferComandi() {
    bool booleanoComandi = true;
    static char comando[50];
    while (booleanoComandi) {
        printf("Inseriesci dei comandi, scrivi HELP se vuoi vedere la lista dei comandi: \n");
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
        printf("'DIFFICOLTA' seleziona difficolta di gioco\n");
        printf("'SCAN' stampa informazioni riguardanti la partita\n");
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
        printf("-------------------------------------------\n");
        printf("SCELTA DIFFICOLTA\n");
        modificaDifficolta(&numeroDiNaviInviati, &secondiDiReazione, &possibilitaDiSuccessoTrasferimentoComputerNavi);
        printf("-------------------------------------------\n");
    } else if (strcmp(inputUtente, arrayComando[4]) == 0) {
        printf("-------------------------------------------\n");
        printf("#################SCANNER-REPORT####################\n");
        printf("#################NAVI PLAYER####################\n");
        printf("... scanning ...\n");
        printf("Totalenavi player:\n");
        printf("navi caccia: %d\n", player.cacciaPlayer);
        printf("navi intercettatori: %d\n", player.intercettatorePlayer);
        printf("navi bombardieri: %d\n", player.bombardierePlayer);
        ///
        printf("#################NAVI COMPUTER####################\n");
        printf("Totalenavi computer: \n");
        printf("navi caccia: %d\n", VaaxNpc.cacciaComputer);
        printf("navi intercettatori: %d\n", VaaxNpc.intercettatoreComputer);
        printf("navi bombardieri: %d\n", VaaxNpc.bombardiereComputer);
        printf("#################PIANETTA-A SCAN####################\n");
        // NAVI PLAYER
        printf("NAVI DEL PLAYER IN PIANETA A\n");
        printf("navi caccia: %d\n", pianetaA.cacciaPlayer);
        printf("navi intercettatori: %d\n", pianetaA.intercettatorePlayer);
        printf("navi bombardieri: %d\n", pianetaA.bombardierePlayer);
        // NAVI COMPUTER
        printf("NAVI DEL COMPUTER IN PIANETA A\n");
        printf("navi caccia: %d\n", pianetaA.cacciaComputer);
        printf("navi intercettatori: %d\n", pianetaA.intercettatoreComputer);
        printf("navi bombardieri: %d\n", pianetaA.bombardiereComputer);

        printf("#################SCANNER-END####################\n");
        printf("-------------------------------------------\n");
    } else if (strcmp(inputUtente, arrayComando[5]) == 0) {
        printf("RITORNO A MAIN\n");
        return whileComandi = false;
    } else if (strcmp(inputUtente, arrayComando[6]) == 0) {
        printf("FINE PROGRAMMA..");
        exit(1);
    }

}

// inizio programma
int main () {

    static char startCommand[10];
    printf("scrivi START per cominciare\n");
    scanf("%10s", &startCommand);
    if (strcmp(startCommand, "START") == 0) {
        printf("Partita cominciata\n");
    } else {
        printf("NO\n");
        return 0;
    }


    pthread_t timerMandareNavi, timerGuerraTimer; 


    printf("bot inizio programma, iniziera' mandare ogni 10 secondi 5 caccia in pianeta A\n");
    pthread_create(&timerMandareNavi, NULL, computerAction, &secondiDiReazione);
    pthread_create(&timerGuerraTimer, NULL, battagliaInTotTempo, NULL);

    printf("threads partiti\n");


    // configurazione init a 0 di struct Giocatori
    // configuro la prompt comandi 
    // ----------------------------------------------------------------------------------------------
    // ------------------------------------PROMPTS COMMANDI GIOCO -----------------------------------
    // ----------------------------------------------------------------------------------------------


    while (whileComandi == true) { 
        char *inputUtente = bufferComandi(); 
        risposteComandi(inputUtente);
    }
    printf("#################SCANNER-REPORT####################\n");
    printf("Totalenavi player: %d\n", player.cacciaPlayer);
    printf("Totale navi player in pianeta a : %d\n", pianetaA.cacciaPlayer);
    ///
    printf("#################separatore####################\n");
    printf("Totalenavi computer: %d\n", VaaxNpc.cacciaComputer);
    printf("Totale navi del computer in pianeta a : %d\n", pianetaA.cacciaComputer);
    printf("#################swaggerend####################\n");
    //funziona anche senza questa pthreadexit Clean clode
    return 0;
}


