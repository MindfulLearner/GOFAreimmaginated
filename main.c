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

const char *sceltaNavi[] = {
    "LISTANAVI", 
    "CACCIA",
    "INTERCETTATORE",
    "BOMBARDIERE",
    "ESCI"
};

//Parametri di difficolta DEFAULT EASy, non si puo mettere in una data structure in cui praticamente viene richiamato solo quello
//e modifica i parametri da li
int numeroDiNaviInviati = 8;
int secondiDiReazione = 10;
int possibilitaDiSuccessoTrasferimentoComputerNavi = 6;
int secondiPerBattaglia = 20;


// DIFFICOLTA EASY IN DEFAULT>?a
static char difficolta[10] = "EASY";

void modificaDifficolta(int* invieraNavi, int* secondiTot, int* possibilitaDiSuccesso, int* swag) {
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
        secondiPerBattaglia = 20;
        printf("Adesso computer inviera tra 1 a %d navi ogni %d secondi la probalita successo: %d su 10\n", *invieraNavi, *secondiTot, *possibilitaDiSuccesso);
        printf("Ci saranno le battaglie ogni %d\n", secondiPerBattaglia);
        printf("HAI SELEZIONATO EASY\n");

    } else if (strcmp(difficolta, sceltaDifficolta[1]) == 0){
        printf("HAI SELEZIONATO MEDIUM\n");
        numeroDiNaviInviati = 15;
        secondiDiReazione = 6;
        possibilitaDiSuccessoTrasferimentoComputerNavi = 7;
        secondiPerBattaglia = 10;
        printf("Adesso computer inviera tra 1 a %d navi ogni %d secondi la probalita successo: %d su 10\n", *invieraNavi, *secondiTot, *possibilitaDiSuccesso);
        printf("Ci saranno le battaglie ogni %d\n", secondiPerBattaglia);
        //piu leggibile con else if altrimenti con solo else non cambierebbe
    } else if (strcmp(difficolta, sceltaDifficolta[2]) == 0){
        printf("HAI SELEZIONATO HARD\n");
        numeroDiNaviInviati = 30;
        secondiDiReazione = 3;
        possibilitaDiSuccessoTrasferimentoComputerNavi = 9;
        secondiPerBattaglia = 8; 
        printf("Adesso computer inviera tra 1 a %d navi ogni %d secondi la probalita successo: %d su 10\n", *invieraNavi, *secondiTot, *possibilitaDiSuccesso);
        printf("Ci saranno le battaglie ogni %d\n", secondiPerBattaglia);

    }

}

// in base alla difficolta, verranno cambiati i praramentri di mandaNAviComputer
void mandaNaviComputer(int* randomNumeroNaviInviati, computer *vaaxNpc, pianeta *pianetaA){
    srand(time(NULL));
    int randomGeneratoNaviInviati = (rand() % (*randomNumeroNaviInviati)) + 1;
    // printf("random: %d\n", randomGeneratoNaviInviati);
    // ora probabilita che vengano mandati le navi 
    srand(time(NULL)); 
    int randomSuccessNumb = (rand() % 10) + 1; 
    int randomTipoDiNavi = (rand() % 3) + 1;
    if (randomTipoDiNavi == 1) {
        if (randomSuccessNumb <= possibilitaDiSuccessoTrasferimentoComputerNavi) {
            //        printf("%d <= %d successo\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
            // parti di codice non necessari, ma necessari in caso si volessero aggiungere altre logiche a riguardo
            vaaxNpc->cacciaComputer = vaaxNpc->cacciaComputer + randomGeneratoNaviInviati;
            //qui 
            pianetaA->cacciaComputer += vaaxNpc->cacciaComputer; 
            vaaxNpc->cacciaComputer = vaaxNpc->cacciaComputer - randomGeneratoNaviInviati;
        } else {
            //      printf("%d > %d fallimento\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
        }
    } else if (randomTipoDiNavi == 2) {
        if (randomSuccessNumb <= possibilitaDiSuccessoTrasferimentoComputerNavi) {
            //        printf("%d <= %d successo\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
            // parti di codice non necessari, ma necessari in caso si volessero aggiungere altre logiche a riguardo
            vaaxNpc->intercettatoreComputer = vaaxNpc->intercettatoreComputer + randomGeneratoNaviInviati;
            //qui 
            pianetaA->intercettatoreComputer += vaaxNpc->intercettatoreComputer; 
            vaaxNpc->intercettatoreComputer = vaaxNpc->intercettatoreComputer - randomGeneratoNaviInviati;
        } else {
            //      printf("%d > %d fallimento\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
        }
    } else if (randomTipoDiNavi == 3) {
        if (randomSuccessNumb <= possibilitaDiSuccessoTrasferimentoComputerNavi) {
            //        printf("%d <= %d successo\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
            // parti di codice non necessari, ma necessari in caso si volessero aggiungere altre logiche a riguardo
            vaaxNpc->bombardiereComputer = vaaxNpc->bombardiereComputer + randomGeneratoNaviInviati;
            //qui 
            pianetaA->bombardiereComputer += vaaxNpc->bombardiereComputer; 
            vaaxNpc->bombardiereComputer = vaaxNpc->bombardiereComputer - randomGeneratoNaviInviati;
        } else {
            //      printf("%d > %d fallimento\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
        }
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
    int* secondiPerBattaglia = (int*)arg; 
    // printf("entrato in battaglia tempo tot\n");
    while (timerBool) {
        for (int timer = *secondiPerBattaglia; timer > 0; timer --) {
            sleep(1);
        }

/* 
 LOGICA DELLA BATTAGLIA 
- considerazioni carta forbice e sasso
#CARTA CACCIA
win rate di carta vs sasso 8 su 10, se sta su sopra 8 perde
win rate di carta vs forbice 2 su 10 se sta su sopra 2 pered
win rate di carta vs carta 5 su 10 se sta sopra 5 perde
#SASSO INTERCETTATOTRE
win rate di sasso vs forbice 8 su 10, se sta su sopra 8 perde
win rate di sasso vs carta 2 su 10 se sta su sopra 2 pered
win rate di sasso vs sasso 5 su 10 se sta sopra 5 perde
#FORBICE BOMBARDIERE
win rate di forbice vs carta 8 su 10, se sta su sopra 8 perde
win rate di forbice vs sasso 2 su 10 se sta su sopra 2 pered
win rate di forbice vs forbice 5 su 10 se sta sopra 5 perde

carta'caccia' > sasso'intercettatore' > forbice'bombardiere' > (RICOMINCIA) carta... 

attaccante sara sempre il player, quindi
si useranno le truppe di player per attaccare computer, le probabilita sia per attaccante che difensore sara sempre uguale
cambiera solo tramite il numero di truppe che ci sono

come si svolgera'? 

randomNum da 1 a 3
examp: se esce 2 
2 = intercettatorePLAYER 
attacchera!
random da 1 a 3 
esce 1
1 = cacciaComputer

intercettatore avra un 2 su 10 per battere caccia
perche sasso vs carta e 2 su 10

il ciclo continuera fino a quando o player o computer avranno 0 truppe

da implementare poi chi ha il dominio del pianeta

*/

        // printf("battaglia in corso..\n");
    }
    pthread_exit(NULL);
}




void stampaTipologieDiNavi() {
    printf("----------------------TIPOLOGIA NAVI-------------------------------\n");
    printf("'CACCIA' navi che counterano i BOMBARDIERI\n");
    printf("'INTERCETTATORE' navi che counterano i CACCIA\n");
    printf("'BOMBARIERE' navi che counterano gli INTERCETTATORI\n");
    printf("'ESCI' per uscire dal comnado mandaNavi\n");
    printf("----------------------------------------------------------------\n");
}

void comparazionePianetiInvioNavi(int naviDaMandare, char nomeDelPianeta[50], giocatore *player, pianeta *pianetaA, char comandoMandaNavi[50]) {
    // comparazione nome pianeta e pianeti list
    // printf("%d\n", player->cacciaPlayer);
    if (strcmp(nomeDelPianeta, pianetiList[0]) == 0) {
        // meno a player + a pianeta selezionato
        // CONTROLLO NAVI FUNZIONANATE
        if (strcmp(comandoMandaNavi, sceltaNavi[1]) == 0)  {
            if (player->cacciaPlayer > naviDaMandare) {
                player->cacciaPlayer -= naviDaMandare;
                pianetaA->cacciaPlayer += naviDaMandare;
            } else {
                printf("NON HAI ABBASTANZA CACCIA DA MANDARE\n");
            }
        }
        if (strcmp(comandoMandaNavi, sceltaNavi[2]) == 0)  {
            if (player->intercettatorePlayer > naviDaMandare) {
                player->intercettatorePlayer -= naviDaMandare;
                pianetaA->intercettatorePlayer += naviDaMandare;
            } else {
                printf("NON HAI ABBASTANZA INTERCETTATORI DA MANDARE\n");
            }
        }
        if (strcmp(comandoMandaNavi, sceltaNavi[3]) == 0)  {
            if (player->bombardierePlayer > naviDaMandare) {
                player->bombardierePlayer -= naviDaMandare;
                pianetaA->bombardierePlayer += naviDaMandare;
            } else {
                printf("NON HAI ABBASTANZA BOMBARDIERI DA MANDARE\n");
            }
        }
    }
}
//mandaNavi funzioner
// AGGIUNGERE IF DI CONTROLLO SE PRESENTI SE POSSIBILE 
void mandaNavi(giocatore *player, pianeta *pianetaA){
    int naviDaMandare;
    static char nomeDelPianeta[50];
    static char comandoMandaNavi[50];
    while(1) {
        printf("Quali navi vuoi mandare? Scrivi 'LISTANAVI' per vedere quali hai a disposizione\n");
        scanf("%49s", &comandoMandaNavi);
        if (strcmp(comandoMandaNavi, sceltaNavi[0]) == 0){
            // tipologia navi 
            stampaTipologieDiNavi();
        } else if (strcmp(comandoMandaNavi, sceltaNavi[1]) == 0){
            // caccia
            printf("Quanti navi caccia vuoi mandare?\n");
            scanf("%d", &naviDaMandare);
            printf("In che pianeta vuoi mandarli?\n");
            printf("Puoi inviarli in:\n");
            printf("PIANETA-A\n");
            printf("PIANETA-B\n");
            scanf("%49s", &nomeDelPianeta);
            // printf("%d\n", player->cacciaPlayer);
            comparazionePianetiInvioNavi(naviDaMandare, nomeDelPianeta, player, pianetaA, comandoMandaNavi);
            printf("hai mandato %d caccia\n", naviDaMandare);
            break;
        } else if (strcmp(comandoMandaNavi, sceltaNavi[2]) == 0){
            //inter
            printf("Quanti navi bombardieri vuoi mandare?\n");
            scanf("%d", &naviDaMandare);
            printf("In che pianeta vuoi mandarli?\n");
            printf("Puoi inviarli in:\n");
            printf("PIANETA-A\n");
            printf("PIANETA-B\n");
            scanf("%49s", &nomeDelPianeta);
            comparazionePianetiInvioNavi(naviDaMandare, nomeDelPianeta, player, pianetaA, comandoMandaNavi);
            printf("hai mandato %d caccia\n", naviDaMandare);
            break;
        } else if (strcmp(comandoMandaNavi, sceltaNavi[3]) == 0){
            // bomb
            printf("Quanti navi bombardieri vuoi mandare?\n");
            scanf("%d", &naviDaMandare);
            printf("In che pianeta vuoi mandarli?\n");
            printf("Puoi inviarli in:\n");
            printf("PIANETA-A\n");
            printf("PIANETA-B\n");
            scanf("%49s", &nomeDelPianeta);
            comparazionePianetiInvioNavi(naviDaMandare, nomeDelPianeta, player, pianetaA, comandoMandaNavi);
            printf("hai mandato %d caccia\n", naviDaMandare);
            break;
        } else if (strcmp(comandoMandaNavi, sceltaNavi[4]) == 0){
            printf("ritorno Lobby\n");
            break;
        }
    }
}


// produci navi da mettere poi limite
void produciNavi(giocatore *player) {
    int nuoveNavi;

    // che tipo di navi vuoi produrre??
    char comandoProduciNavi[20];
    printf("Che navi vuoi produrre?\n");
    printf("Scrivi 'LISTANAVI' se vuoi vedere i tipi di navi\n");
    while(1) {
        scanf("%20s", comandoProduciNavi);
        if (strcmp(comandoProduciNavi, sceltaNavi[0]) == 0) {
            stampaTipologieDiNavi();
        } else if (strcmp(comandoProduciNavi, sceltaNavi[1]) == 0) {
            printf("Quanti CACCIA vuoi produrre\n");
            scanf("%d", &nuoveNavi);
            player->cacciaPlayer += nuoveNavi;
            printf("Hai prodotto %d caccia\n", nuoveNavi);
            break;
        } else if (strcmp(comandoProduciNavi, sceltaNavi[2]) == 0) {
            printf("Quanti INTERCETTATORI vuoi produrre\n");
            scanf("%d", &nuoveNavi);
            player->intercettatorePlayer += nuoveNavi;
            printf("Hai prodotto %d intercettatore\n", nuoveNavi);
            break;
        } else if (strcmp(comandoProduciNavi, sceltaNavi[3]) == 0) {
            printf("Quanti BOMBARDIERI vuoi produrre\n");
            scanf("%d", &nuoveNavi);
            player->bombardierePlayer += nuoveNavi;
            printf("Hai prodotto %d bombardieri\n", nuoveNavi);
            break;
        } else if (strcmp(comandoProduciNavi, sceltaNavi[4]) == 0) {
            printf("Uscita da produciNavi\n");
            break;
        }else {
            printf("Nave inestistente scrivi 'LISTANAVI' per vedere la lista di navi\n");
        }
    }
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
        modificaDifficolta(&numeroDiNaviInviati, &secondiDiReazione, &possibilitaDiSuccessoTrasferimentoComputerNavi, &secondiPerBattaglia);
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
    pthread_create(&timerGuerraTimer, NULL, battagliaInTotTempo, &secondiPerBattaglia);

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
