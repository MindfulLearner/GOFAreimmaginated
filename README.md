# GOFAreimagined

## Informazioni utili
GOFA era uno dei miei giochi preferiti in assoluto. Era perfetto e ci ho speso dei soldi quando ero piccolo, e avevo un gruppo di amici inglesi con cui gicoavo e coordinavamo gli attacchi insieme.
Questo codice è stato scritto con l'obiettivo di consolidare le mia abilità in C, per ora non ci saranno ancora pointer o almeno non così tanti, per ora è un progetto base che dovrà poi essere sistemato tramite organizzazione data structure etc..

## Cos'è GOFA
Benvenuti in questo gioco, GOFA sta per Galaxy on Fire Alliances un vecchio gioco per Android e Ios, purtroppo per "Budget" non sono riusciti a tenere i server aperti di conseguenza chiudendo il server stesso.
Ora detto ciò inizia a spiegare che questa versione del gioco sarà solo una parte del gameplay dato che costruire tutto il sistemo sarebbe una roba assurda ma se decidessi mai di farlo o in parte consdiererò.

## Gofareimmaginated
ci saranno un player e un computer che cercheranno di prendere i pianeti facendo fare delle battaglia a tempo prestabilito di secondi stile carta forbice e sasso.
l'obbiettivo del gioco sara di conquistare tutti i 3 pianeti cercando di opprevedere lemosse dell'altro tramite una funzione scan che fa vedere al player che cosa sta arrivando su un pianeta o cosa ci sara

## Cosa potra fare il player? 
Il player potra fare semplici cose tramite dei comandi che verranno messi sul terminale:
1. Scan = potra farlo un tot numero di volte e permettera di vedere quante navi ci sono in un pianeta e se ci saranno in arrivo altre navi. l'idea sarebbe mettere anche una probabilita di successo ma diventerebbe troppo complicato.
2. Send = potra mandare truppe in un pianeta a scelta e a seconda della proprieta del pianeta saranno o in difesa o in attacco ovviamente faranno le battaglie solo in certi momenti del tempo.
3. InfoBattleTime = dira gli orari di battaglia per ogni pianeta.

## Il computer invece? 
Per ora puo solo mandare navi in modo casuale tra i vari pianeti. Produrra meno navi rispetto il giocatore quindi stai tranquillo.
Ovviamente seguira anche lui gli orari di battaglia e posizionamento difesa e attacco

# TASKFORCE
- creare pianeta Casa che dovra essere il pianeta da cui il giocatore mandera le truppe
- capire come gestire il tempo e come fare in modo che possa produrre e metterci circa alcuni secondi per avere le truppe pronte per essere mandate quindi degli if tot truppe che posso mandare se esistenti.
- Pianeta A questo sara il primo pianeta che dovra essere conquistato dal player per ora in cui verranno fatti alcuni test per il funzionamento 
- Computer dovra generare dei numeri randomici per fare in modo che la scelta di mandare truppe di qualche tipo sara abbastanza casuale 
- Impostare intercettatori, caccia e bombardieri, deve essere riconosciuto navi del gicatori e navi del computer. 
