#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include <string.h>



// // Giocatore e Computer
// typedef struct { 
// 	int giocatoreNaviCaccia 
// } Giocatore;
// 
// // Pianeti
// typedef struct { 
// 	int giocatoreNaviCaccia;
// } PianetaA;
// 
// //inizializzazione Giocatore a 0
// int initGiocatore {
// }


// 	//SPOSTIAMO INT DI struct giocatore a struct pianeta
// void giocatoreMoveNavi (){
// }
// 


const char *arrayComando[] = {
    "HELP",
    "PRODUCINAVI",
    "MANDANAVI",
    "EXIT"
}; 

char* richiestaComandi() {
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
S COMMANDI GIOCO -----------------------------------
    // ----------------------------------------------------------------------------------------------

    while (true) { 
        char *inputUtente = richiestaComandi(); 
        printf("%s\n", inputUtente);
        risposteComandi(inputUtente);
    }

    return 0;
}

















