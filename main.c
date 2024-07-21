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
// void giocatoreProduciNavi () {
// 	// richiesta di produzione navi si controll si parte dal presssuposto che verra usata questa richiest 	
// }

const char *arrayComando[] = {
    "help",
    "produciNavi",
    "mandaNavi"
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
        printf("Comando Errato riprova\n");
    }
}

void risposteComandi(const char* inputUtente) {
    if (strcmp(inputUtente, arrayComando[0]) == 0) {
        printf("I comandi che hai a disposizione sono:\n");
        printf("tutorial\n");
        printf("produciNavi\n");
        printf("mandaNavi\n");
    } else if (strcmp(inputUtente, arrayComando[1]) == 0) {
        printf("PRODUCINAVISWAG\n");
    } else if (strcmp(inputUtente, arrayComando[2]) == 0) {
        printf("MANDANAVI\n");
    }
}

// inizio programma
int main () {
    // configurazione init a 0 di struct Giocatori
    // configuro la prompt comandi 
    // ----------------------------------------------------------------------------------------------
    // ------------------------------------PROMPTS COMMANDI GIOCO -----------------------------------
    // ----------------------------------------------------------------------------------------------


    while (true) { 
        char *inputUtente = richiestaComandi(); 
        printf("%s\n", inputUtente);
        risposteComandi(inputUtente);
    }






    return 0;
}

















