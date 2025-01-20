// avevo pushato ma
//// AGGIUNGERE ERRORI SUI NUMERI QUANDO si scrive, aggiungere errori su scritte sbagliate

// ma perche non mi pusha bene non mi funziona l'account per pushare
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef struct
{
    int cacciaPlayer;
    int intercettatorePlayer;
    int bombardierePlayer;
} giocatore;
typedef struct
{
    int cacciaComputer;
    int intercettatoreComputer;
    int bombardiereComputer;
} computer;
typedef struct
{
    // PLAYER NAVI
    int cacciaPlayer;
    int intercettatorePlayer;
    int bombardierePlayer;
    // COMPUTER NAVI
    int cacciaComputer;
    int intercettatoreComputer;
    int bombardiereComputer;
} pianeta;

// funzione per clearrare il codice
void cleanse()
{
    system("clear");
};

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
    "USCITATOTALE"};

const char *sceltaDifficolta[] = {
    "EASY",
    "MEDIUM",
    "HARD"};

const char *sceltaNavi[] = {
    "LISTANAVI",
    "CACCIA",
    "INTERCETTATORE",
    "BOMBARDIERE",
    "ESCI"};

int quandoCeLaBattaglia;
int quantoArrivanoINemici;

// Parametri di difficolta DEFAULT EASy, non si puo mettere in una data structure in cui praticamente viene richiamato solo quello
// e modifica i parametri da li
int numeroDiNaviInviati = 8;
int secondiDiReazione = 10;
int possibilitaDiSuccessoTrasferimentoComputerNavi = 6;
int secondiPerBattaglia = 20;

// DIFFICOLTA EASY IN DEFAULT>?a
static char difficolta[10] = "EASY";

void modificaDifficolta(int *invieraNavi, int *secondiTot, int *possibilitaDiSuccesso, int *swag)
{
    printf("selezioan una difficolta:\n");
    printf("EASY\n");
    printf("MEDIUM\n");
    printf("HARD\n");
    static char contenitoreScanf[10];
    scanf("%10s", contenitoreScanf);
    // si usa stcpy libreria che copia altrimenti bisogna fare tutto un calcolo di array per copiare qualcosa
    strcpy(difficolta, contenitoreScanf);
    printf("DIFFICOLTA SELEZIONATA: %s\n", difficolta);

    if (strcmp(difficolta, sceltaDifficolta[0]) == 0)
    {
        printf("HAI SELEZIONATO EASY\n");
        numeroDiNaviInviati = 8;
        secondiDiReazione = 10;
        possibilitaDiSuccessoTrasferimentoComputerNavi = 6;
        secondiPerBattaglia = 20;
        printf("Adesso computer inviera tra 1 a %d navi ogni %d secondi la probalita successo: %d su 10\n", *invieraNavi, *secondiTot, *possibilitaDiSuccesso);
        printf("Ci saranno le battaglie ogni %d\n", secondiPerBattaglia);
        printf("HAI SELEZIONATO EASY\n");
    }
    else if (strcmp(difficolta, sceltaDifficolta[1]) == 0)
    {
        printf("HAI SELEZIONATO MEDIUM\n");
        numeroDiNaviInviati = 15;
        secondiDiReazione = 6;
        possibilitaDiSuccessoTrasferimentoComputerNavi = 7;
        secondiPerBattaglia = 10;
        printf("Adesso computer inviera tra 1 a %d navi ogni %d secondi la probalita successo: %d su 10\n", *invieraNavi, *secondiTot, *possibilitaDiSuccesso);
        printf("Ci saranno le battaglie ogni %d\n", secondiPerBattaglia);
        // piu leggibile con else if altrimenti con solo else non cambierebbe
    }
    else if (strcmp(difficolta, sceltaDifficolta[2]) == 0)
    {
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
void mandaNaviComputer(int *randomNumeroNaviInviati, computer *vaaxNpc, pianeta *pianetaA)
{
    srand(time(NULL));
    int randomGeneratoNaviInviati = (rand() % (*randomNumeroNaviInviati)) + 1;
    // printf("random: %d\n", randomGeneratoNaviInviati);
    // ora probabilita che vengano mandati le navi
    srand(time(NULL));
    int randomSuccessNumb = (rand() % 10) + 1;
    int randomTipoDiNavi = (rand() % 3) + 1;
    if (randomTipoDiNavi == 1)
    {
        if (randomSuccessNumb <= possibilitaDiSuccessoTrasferimentoComputerNavi)
        {
            //        printf("%d <= %d successo\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
            // parti di codice non necessari, ma necessari in caso si volessero aggiungere altre logiche a riguardo
            vaaxNpc->cacciaComputer = vaaxNpc->cacciaComputer + randomGeneratoNaviInviati;
            // qui
            pianetaA->cacciaComputer += vaaxNpc->cacciaComputer;
            vaaxNpc->cacciaComputer = vaaxNpc->cacciaComputer - randomGeneratoNaviInviati;
        }
        else
        {
            //      printf("%d > %d fallimento\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
        }
    }
    else if (randomTipoDiNavi == 2)
    {
        if (randomSuccessNumb <= possibilitaDiSuccessoTrasferimentoComputerNavi)
        {
            //        printf("%d <= %d successo\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
            // parti di codice non necessari, ma necessari in caso si volessero aggiungere altre logiche a riguardo
            vaaxNpc->intercettatoreComputer = vaaxNpc->intercettatoreComputer + randomGeneratoNaviInviati;
            // qui
            pianetaA->intercettatoreComputer += vaaxNpc->intercettatoreComputer;
            vaaxNpc->intercettatoreComputer = vaaxNpc->intercettatoreComputer - randomGeneratoNaviInviati;
        }
        else
        {
            //      printf("%d > %d fallimento\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
        }
    }
    else if (randomTipoDiNavi == 3)
    {
        if (randomSuccessNumb <= possibilitaDiSuccessoTrasferimentoComputerNavi)
        {
            //        printf("%d <= %d successo\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
            // parti di codice non necessari, ma necessari in caso si volessero aggiungere altre logiche a riguardo
            vaaxNpc->bombardiereComputer = vaaxNpc->bombardiereComputer + randomGeneratoNaviInviati;
            // qui
            pianetaA->bombardiereComputer += vaaxNpc->bombardiereComputer;
            vaaxNpc->bombardiereComputer = vaaxNpc->bombardiereComputer - randomGeneratoNaviInviati;
        }
        else
        {
            //      printf("%d > %d fallimento\n", randomSuccessNumb, possibilitaDiSuccessoTrasferimentoComputerNavi);
        }
    }
}

volatile bool timerBool = true;
// funziona nache senza argomento void pointer, ncesario void per un pthread, e poi utilizzo di varibiabile con casting putnartore con arg
// per fare in modo di utilizzare arg, altrimenti dato che arg e' in void
// qualsiasi modo per richiamarlo putnera sempre su putnatore su indirizzo di memoria
//
void *computerAction(void *arg)
{
    int *secondiDiReazione = (int *)arg; // castiamo puntatore void inint
    while (timerBool)
    {
        for (int timer = *secondiDiReazione; timer > 0; timer--)
        {
            sleep(1);
            // printf("%d\n", timer);
        }
        mandaNaviComputer(&numeroDiNaviInviati, &VaaxNpc, &pianetaA);
    }
    pthread_exit(NULL);
}

int naveInDifesa(int numeroRandomDaUnoATre)
{
    srand(time(NULL));
    
    // CACCIA (CARTA) IN ATTACCO
    if (numeroRandomDaUnoATre == 1) // Computer difende con Caccia
    {
        int winRate = (rand() % 10) + 1;
        printf("Caccia VS Caccia\n");
        
        if (winRate > 5) // 50% possibilità
        {
            printf("Vittoria! (WinRate: %d/10)\n", winRate);
            return 1;
        }
        else 
        {
            printf("Sconfitta! (WinRate: %d/10)\n", winRate);
            return 0;
        }
    }
    else if (numeroRandomDaUnoATre == 2) // Computer difende con Intercettatore
    {
        int winRate = (rand() % 10) + 1;
        printf("Caccia VS Intercettatore\n");
        
        if (winRate <= 8) // 80% possibilità
        {
            printf("Vittoria! (WinRate: %d/10)\n", winRate);
            return 1;
        }
        else 
        {
            printf("Sconfitta! (WinRate: %d/10)\n", winRate);
            return 0;
        }
    }
    else if (numeroRandomDaUnoATre == 3) // Computer difende con Bombardiere
    {
        int winRate = (rand() % 10) + 1;
        printf("Caccia VS Bombardiere\n");
        
        if (winRate <= 2) // 20% possibilità
        {
            printf("Vittoria! (WinRate: %d/10)\n", winRate);
            return 1;
        }
        else 
        {
            printf("Sconfitta! (WinRate: %d/10)\n", winRate);
            return 0;
        }
    }
    return -1;
}

// Aggiungiamo due nuove funzioni per gli altri tipi di navi
int intercettatoreInAttacco(int difesaComputer)
{
    srand(time(NULL));
    
    if (difesaComputer == 1) // VS Caccia
    {
        int winRate = (rand() % 10) + 1;
        printf("Intercettatore VS Caccia\n");
        
        if (winRate <= 2) // 20% possibilità
        {
            printf("Vittoria! (WinRate: %d/10)\n", winRate);
            return 1;
        }
        else 
        {
            printf("Sconfitta! (WinRate: %d/10)\n", winRate);
            return 0;
        }
    }
    else if (difesaComputer == 2) // VS Intercettatore
    {
        int winRate = (rand() % 10) + 1;
        printf("Intercettatore VS Intercettatore\n");
        
        if (winRate > 5) // 50% possibilità
        {
            printf("Vittoria! (WinRate: %d/10)\n", winRate);
            return 1;
        }
        else 
        {
            printf("Sconfitta! (WinRate: %d/10)\n", winRate);
            return 0;
        }
    }
    else if (difesaComputer == 3) // VS Bombardiere
    {
        int winRate = (rand() % 10) + 1;
        printf("Intercettatore VS Bombardiere\n");
        
        if (winRate <= 8) // 80% possibilità
        {
            printf("Vittoria! (WinRate: %d/10)\n", winRate);
            return 1;
        }
        else 
        {
            printf("Sconfitta! (WinRate: %d/10)\n", winRate);
            return 0;
        }
    }
    return -1;
}

int bombardiereInAttacco(int difesaComputer)
{
    srand(time(NULL));
    
    if (difesaComputer == 1) // VS Caccia
    {
        int winRate = (rand() % 10) + 1;
        printf("Bombardiere VS Caccia\n");
        
        if (winRate <= 8) // 80% possibilità
        {
            printf("Vittoria! (WinRate: %d/10)\n", winRate);
            return 1;
        }
        else 
        {
            printf("Sconfitta! (WinRate: %d/10)\n", winRate);
            return 0;
        }
    }
    else if (difesaComputer == 2) // VS Intercettatore
    {
        int winRate = (rand() % 10) + 1;
        printf("Bombardiere VS Intercettatore\n");
        
        if (winRate <= 2) // 20% possibilità
        {
            printf("Vittoria! (WinRate: %d/10)\n", winRate);
            return 1;
        }
        else 
        {
            printf("Sconfitta! (WinRate: %d/10)\n", winRate);
            return 0;
        }
    }
    else if (difesaComputer == 3) // VS Bombardiere
    {
        int winRate = (rand() % 10) + 1;
        printf("Bombardiere VS Bombardiere\n");
        
        if (winRate > 5) // 50% possibilità
        {
            printf("Vittoria! (WinRate: %d/10)\n", winRate);
            return 1;
        }
        else 
        {
            printf("Sconfitta! (WinRate: %d/10)\n", winRate);
            return 0;
        }
    }
    return -1;
}

void *battagliaInTotTempo(void *arg)
{
    int *secondiPerBattaglia = (int *)arg;
    int dominioPianeta = 0; 
    int contatoreDominio = 0;
    
    while (timerBool)
    {
        // Visualizzazione conto alla rovescia
        printf("\033[2J\033[H"); // Clear screen
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║                  STATO DEL PIANETA                     ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        
        for (int timer = *secondiPerBattaglia; timer > 0; timer--)
        {
            printf("\033[2J\033[H"); // Clear screen
            printf("╔════════════════════════════════════════════════════════╗\n");
            printf("║             PROSSIMA BATTAGLIA TRA: %2d                ║\n", timer);
            printf("╚════════════════════════════════════════════════════════╝\n");
            sleep(1);
            quandoCeLaBattaglia = timer;
        }

        printf("\033[2J\033[H"); // Clear screen
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║                 BATTAGLIA IN CORSO!                     ║\n");
        printf("╚════════════════════════════════════════════════════════╝\n");
        
        for (int t = 2; t > 0; t--)
        {
            sleep(1);
        }
        
        int naviPlayer = pianetaA.cacciaPlayer + pianetaA.intercettatorePlayer + pianetaA.bombardierePlayer;
        int naviComputer = pianetaA.cacciaComputer + pianetaA.intercettatoreComputer + pianetaA.bombardiereComputer;
        
        if (naviPlayer == 0 || naviComputer == 0) {
            printf("\n⚠️  Non ci sono abbastanza navi per combattere! ⚠️\n");
            continue;
        }

        srand(time(NULL));
        int randomAttaccoPlayerNave = (rand() % 3) + 1;
        int randomDifesaComputer = (rand() % 3) + 1;
        int risultatoBattaglia;

        printf("\n🚀 FASE DI COMBATTIMENTO 🚀\n");
        printf("════════════════════════════\n");

        // Gestione battaglia
        if (randomAttaccoPlayerNave == 1)
            risultatoBattaglia = naveInDifesa(randomDifesaComputer);
        else if (randomAttaccoPlayerNave == 2)
            risultatoBattaglia = intercettatoreInAttacco(randomDifesaComputer);
        else if (randomAttaccoPlayerNave == 3)
            risultatoBattaglia = bombardiereInAttacco(randomDifesaComputer);

        // Gestione risultato battaglia e dominio
        if (risultatoBattaglia == 1)
        {
            printf("\n🎯 VITTORIA DEL PLAYER!\n");
            // Rimuovi nave computer
            if (randomDifesaComputer == 1 && pianetaA.cacciaComputer > 0)
                pianetaA.cacciaComputer--;
            else if (randomDifesaComputer == 2 && pianetaA.intercettatoreComputer > 0)
                pianetaA.intercettatoreComputer--;
            else if (randomDifesaComputer == 3 && pianetaA.bombardiereComputer > 0)
                pianetaA.bombardiereComputer--;

            if (dominioPianeta <= 0) {
                contatoreDominio = 1;
                dominioPianeta = 0;
            } else {
                contatoreDominio++;
            }

            if (contatoreDominio >= 3 && dominioPianeta != 1) {
                dominioPianeta = 1;
                printf("\n╔════════════════════════════════════════════════════════╗\n");
                printf("║           🎉 PIANETA CONQUISTATO DAL PLAYER! 🎉        ║\n");
                printf("╚════════════════════════════════════════════════════════╝\n");
            }
        }
        else if (risultatoBattaglia == 0)
        {
            printf("\n💥 VITTORIA DEL COMPUTER!\n");
            // Rimuovi nave player
            if (randomAttaccoPlayerNave == 1 && pianetaA.cacciaPlayer > 0)
                pianetaA.cacciaPlayer--;
            else if (randomAttaccoPlayerNave == 2 && pianetaA.intercettatorePlayer > 0)
                pianetaA.intercettatorePlayer--;
            else if (randomAttaccoPlayerNave == 3 && pianetaA.bombardierePlayer > 0)
                pianetaA.bombardierePlayer--;

            if (dominioPianeta >= 0) {
                contatoreDominio = -1;
                dominioPianeta = 0;
            } else {
                contatoreDominio--;
            }

            if (contatoreDominio <= -3 && dominioPianeta != -1) {
                dominioPianeta = -1;
                printf("\n╔════════════════════════════════════════════════════════╗\n");
                printf("║           ⚠️  PIANETA CONQUISTATO DAL COMPUTER! ⚠️      ║\n");
                printf("╚════════════════════════════════════════════════════════╝\n");
            }
        }

        // Visualizzazione stato del pianeta
        printf("\n╔════════════════════════════════════════════════════════╗\n");
        printf("║                   STATO DEL PIANETA                     ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        if (dominioPianeta == 0) {
            printf("║  🌍 STATO: NEUTRALE (Streak: %2d)                        ║\n", contatoreDominio);
        } else if (dominioPianeta == 1) {
            printf("║  👑 STATO: CONTROLLATO DAL PLAYER                       ║\n");
        } else {
            printf("║  ⚔️  STATO: CONTROLLATO DAL COMPUTER                    ║\n");
        }
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║                    NAVI SUL PIANETA                    ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║  PLAYER:                                               ║\n");
        printf("║    🚀 Caccia: %-3d                                      ║\n", pianetaA.cacciaPlayer);
        printf("║    🛸 Intercettatori: %-3d                              ║\n", pianetaA.intercettatorePlayer);
        printf("║    💫 Bombardieri: %-3d                                 ║\n", pianetaA.bombardierePlayer);
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║  COMPUTER:                                             ║\n");
        printf("║    🚀 Caccia: %-3d                                      ║\n", pianetaA.cacciaComputer);
        printf("║    🛸 Intercettatori: %-3d                              ║\n", pianetaA.intercettatoreComputer);
        printf("║    💫 Bombardieri: %-3d                                 ║\n", pianetaA.bombardiereComputer);
        printf("╚════════════════════════════════════════════════════════╝\n\n");

        sleep(3); // Pausa per leggere i risultati
    }
    pthread_exit(NULL);
}

void stampaTipologieDiNavi()
{
    cleanse();
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║                   TIPOLOGIA NAVI                       ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║  🚀 CACCIA         - Efficace contro Bombardieri      ║\n");
    printf("║  🛸 INTERCETTATORE - Efficace contro Caccia           ║\n");
    printf("║  💫 BOMBARDIERE    - Efficace contro Intercettatori   ║\n");
    printf("║  ❌ ESCI           - Torna al menu principale         ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
}

void comparazionePianetiInvioNavi(int naviDaMandare, char nomeDelPianeta[50], giocatore *player, pianeta *pianetaA, char comandoMandaNavi[50])
{
    // comparazione nome pianeta e pianeti list
    // printf("%d\n", player->cacciaPlayer);
    if (strcmp(nomeDelPianeta, pianetiList[0]) == 0)
    {
        // meno a player + a pianeta selezionato
        // CONTROLLO NAVI FUNZIONANATE
        if (strcmp(comandoMandaNavi, sceltaNavi[1]) == 0)
        {
            if (player->cacciaPlayer > naviDaMandare)
            {
                player->cacciaPlayer -= naviDaMandare;
                pianetaA->cacciaPlayer += naviDaMandare;
            }
            else
            {
                cleanse();
                printf("NON HAI ABBASTANZA CACCIA DA MANDARE\n");
            }
        }
        if (strcmp(comandoMandaNavi, sceltaNavi[2]) == 0)
        {
            if (player->intercettatorePlayer > naviDaMandare)
            {
                player->intercettatorePlayer -= naviDaMandare;
                pianetaA->intercettatorePlayer += naviDaMandare;
            }
            else
            {
                cleanse();
                printf("NON HAI ABBASTANZA INTERCETTATORI DA MANDARE\n");
            }
        }
        if (strcmp(comandoMandaNavi, sceltaNavi[3]) == 0)
        {
            if (player->bombardierePlayer > naviDaMandare)
            {
                player->bombardierePlayer -= naviDaMandare;
                pianetaA->bombardierePlayer += naviDaMandare;
            }
            else
            {
                cleanse();
                printf("NON HAI ABBASTANZA BOMBARDIERI DA MANDARE\n");
            }
        }
    }
}
// mandaNavi funzioner
//  AGGIUNGERE IF DI CONTROLLO SE PRESENTI SE POSSIBILE
void mandaNavi(giocatore *player, pianeta *pianetaA)
{
    int naviDaMandare;
    static char nomeDelPianeta[50];
    static char comandoMandaNavi[50];
    while (1)
    {
        printf("Quali navi vuoi mandare? Scrivi 'LISTANAVI' per vedere quali hai a disposizione\n");
        scanf("%49s", comandoMandaNavi);
        if (strcmp(comandoMandaNavi, sceltaNavi[0]) == 0)
        {
            // tipologia navi
            stampaTipologieDiNavi();
        }
        else if (strcmp(comandoMandaNavi, sceltaNavi[1]) == 0)
        {
            // caccia
            printf("Quanti navi caccia vuoi mandare?\n");
            scanf("%d", &naviDaMandare);
            printf("In che pianeta vuoi mandarli?\n");
            printf("Puoi inviarli in:\n");
            printf("PIANETA-A\n");
            printf("PIANETA-B\n");
            scanf("%49s", nomeDelPianeta);
            // printf("%d\n", player->cacciaPlayer);
            comparazionePianetiInvioNavi(naviDaMandare, nomeDelPianeta, player, pianetaA, comandoMandaNavi);
            printf("hai mandato %d caccia\n", naviDaMandare);
            break;
        }
        else if (strcmp(comandoMandaNavi, sceltaNavi[2]) == 0)
        {
            // inter
            printf("Quanti navi bombardieri vuoi mandare?\n");
            scanf("%d", &naviDaMandare);
            printf("In che pianeta vuoi mandarli?\n");
            printf("Puoi inviarli in:\n");
            printf("PIANETA-A\n");
            printf("PIANETA-B\n");
            scanf("%49s", nomeDelPianeta);
            comparazionePianetiInvioNavi(naviDaMandare, nomeDelPianeta, player, pianetaA, comandoMandaNavi);
            printf("hai mandato %d caccia\n", naviDaMandare);
            break;
        }
        else if (strcmp(comandoMandaNavi, sceltaNavi[3]) == 0)
        {
            // bomb
            printf("Quanti navi bombardieri vuoi mandare?\n");
            scanf("%d", &naviDaMandare);
            printf("In che pianeta vuoi mandarli?\n");
            printf("Puoi inviarli in:\n");
            printf("PIANETA-A\n");
            printf("PIANETA-B\n");
            scanf("%49s", nomeDelPianeta);
            comparazionePianetiInvioNavi(naviDaMandare, nomeDelPianeta, player, pianetaA, comandoMandaNavi);
            printf("hai mandato %d caccia\n", naviDaMandare);
            break;
        }
        else if (strcmp(comandoMandaNavi, sceltaNavi[4]) == 0)
        {
            cleanse();
            printf("ritorno Lobby\n");
            break;
        }
    }
}

// produci navi da mettere poi limite
void produciNavi(giocatore *player)
{
    int nuoveNavi;

    // che tipo di navi vuoi produrre??
    char comandoProduciNavi[20];
    printf("Che navi vuoi produrre?\n");
    printf("Scrivi 'LISTANAVI' se vuoi vedere i tipi di navi\n");
    while (1)
    {
        scanf("%20s", comandoProduciNavi);
        if (strcmp(comandoProduciNavi, sceltaNavi[0]) == 0)
        {
            stampaTipologieDiNavi();
        }
        else if (strcmp(comandoProduciNavi, sceltaNavi[1]) == 0)
        {
            printf("Quanti CACCIA vuoi produrre\n");
            scanf("%d", &nuoveNavi);
            player->cacciaPlayer += nuoveNavi;
            printf("Hai prodotto %d caccia\n", nuoveNavi);
            break;
        }
        else if (strcmp(comandoProduciNavi, sceltaNavi[2]) == 0)
        {
            printf("Quanti INTERCETTATORI vuoi produrre\n");
            scanf("%d", &nuoveNavi);
            player->intercettatorePlayer += nuoveNavi;
            printf("Hai prodotto %d intercettatore\n", nuoveNavi);
            break;
        }
        else if (strcmp(comandoProduciNavi, sceltaNavi[3]) == 0)
        {
            printf("Quanti BOMBARDIERI vuoi produrre\n");
            scanf("%d", &nuoveNavi);
            player->bombardierePlayer += nuoveNavi;
            printf("Hai prodotto %d bombardieri\n", nuoveNavi);
            break;
        }
        else if (strcmp(comandoProduciNavi, sceltaNavi[4]) == 0)
        {
            cleanse();
            printf("Uscita da produciNavi\n");
            break;
        }
        else
        {
            cleanse();
            printf("Nave inestistente scrivi 'LISTANAVI' per vedere la lista di navi\n");
        }
    }
};

char *bufferComandi()
{
    bool booleanoComandi = true;
    static char comando[50];
    while (booleanoComandi)
    {
        printf("Inseriesci dei comandi, scrivi HELP se vuoi vedere la lista dei comandi: \n");
        scanf("%49s", comando);
        for (int i = 0; i < sizeof(arrayComando) / sizeof(arrayComando[0]); i++)
        {
            if (strcmp(comando, arrayComando[i]) == 0)
            {
                return comando;
            }
        }
        printf("Comando Errato riprova\n");
    }
}

// comandi di richiesta
bool risposteComandi(const char *inputUtente)
{
    cleanse();
    if (strcmp(inputUtente, arrayComando[0]) == 0)
    {
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║                    LISTA COMANDI                       ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║  📖 HELP         - Mostra questa lista                ║\n");
        printf("║  🏭 PRODUCINAVI  - Costruisci nuove navi             ║\n");
        printf("║  🚀 MANDANAVI    - Invia navi ai pianeti            ║\n");
        printf("║  ⚙️  DIFFICOLTA   - Modifica la difficoltà           ║\n");
        printf("║  🔍 SCAN         - Mostra stato della partita       ║\n");
        printf("║  🔄 EXIT         - Torna alla Lobby                 ║\n");
        printf("║  ❌ USCITATOTALE - Chiudi il gioco                  ║\n");
        printf("╚════════════════════════════════════════════════════════╝\n");
        printf("\nPremi INVIO per continuare...");
        getchar(); // Consuma il newline precedente
        getchar(); // Aspetta che l'utente prema INVIO
    }
    else if (strcmp(inputUtente, arrayComando[1]) == 0)
    {
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║                  PRODUZIONE NAVI                       ║\n");
        printf("╚════════════════════════════════════════════════════════╝\n");
        produciNavi(&player);
    }
    else if (strcmp(inputUtente, arrayComando[2]) == 0)
    {
        printf("Invio Navi:\n");
        mandaNavi(&player, &pianetaA);
    }
    else if (strcmp(inputUtente, arrayComando[3]) == 0)
    {
        printf("Selezione Difficoltà:\n");
        modificaDifficolta(&numeroDiNaviInviati, &secondiDiReazione, &possibilitaDiSuccessoTrasferimentoComputerNavi, &secondiPerBattaglia);
    }
    else if (strcmp(inputUtente, arrayComando[4]) == 0)
    {
        printf("################# SCANNER REPORT ####################\n");
        printf("Prossima battaglia fra %d secondi\n", quandoCeLaBattaglia);
        printf("... scanning ...\n");
        printf("Navi del Giocatore:\n");
        printf("Caccia: %d\n", player.cacciaPlayer);
        printf("Intercettatori: %d\n", player.intercettatorePlayer);
        printf("Bombardieri: %d\n", player.bombardierePlayer);
        printf("Navi del Computer:\n");
        printf("Caccia: %d\n", VaaxNpc.cacciaComputer);
        printf("Intercettatori: %d\n", VaaxNpc.intercettatoreComputer);
        printf("Bombardieri: %d\n", VaaxNpc.bombardiereComputer);
        printf("Navi in Pianeta A - Giocatore:\n");
        printf("Caccia: %d\n", pianetaA.cacciaPlayer);
        printf("Intercettatori: %d\n", pianetaA.intercettatorePlayer);
        printf("Bombardieri: %d\n", pianetaA.bombardierePlayer);
        printf("Navi in Pianeta A - Computer:\n");
        printf("Caccia: %d\n", pianetaA.cacciaComputer);
        printf("Intercettatori: %d\n", pianetaA.intercettatoreComputer);
        printf("Bombardieri: %d\n", pianetaA.bombardiereComputer);
        printf("################# END SCANNER ####################\n");
    }
    else if (strcmp(inputUtente, arrayComando[5]) == 0)
    {
        printf("Ritorno a Main...\n");
        return whileComandi = false;
    }
    else if (strcmp(inputUtente, arrayComando[6]) == 0)
    {
        printf("Fine programma...\n");
        exit(1);
    }
    printf("\nScrivi HELP per vedere i comandi disponibili\n");
    return true;
}

// inizio programma
int main()
{

    static char startCommand[10];
    printf("scrivi START per cominciare\n");
    scanf("%10s", startCommand);
    if (strcmp(startCommand, "START") == 0)
    {
        printf("Partita cominciata\n");
    }
    else
    {
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

    while (whileComandi == true)
    {
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
    // funziona anche senza questa pthreadexit Clean clode
    return 0;
}
