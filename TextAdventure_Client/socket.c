#include "socket.h"


int login()
{
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    char cSaisie[1024];

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    printf("Entrez l'adresse du serveur\n");
    scanf("%s",cSaisie);
    fflush(stdin);
    addr.sin_addr.s_addr = inet_addr(cSaisie); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);

    char c_repenigme[20];// change en fonction du choix du premier joueur
    char c_rep[20];
    int reception = 1;
    int p=1;


    if (connect(server, (SOCKADDR *)&addr, sizeof(addr)) < 0) {
        perror("Connexion échouée\n");
    }
    printf("Connecté !\n");
    system("cls");

    printf("Attendez l'autre joueur\n");
    while (reception) {
        if (recv(server,c_repenigme,sizeof(c_repenigme),0) < 0) {
            return 1;
        }
        if (c_repenigme[0]) {
            reception = 0;
        }

    }
    reception  = 1;

   char c_repenigme2[20]; // chaine a envoyé a l'autre pc
   system("cls");
   lireFichier("intro_enigme2.txt");


   while (p == 1) {
    printf("oignon, oreiller, chaise, robinet . \n"); // les 4 choix

    scanf("%s",c_repenigme2);
    if (strcmp(c_repenigme2,"oignon")==0)// si le joueur entre une autre chaines que les 4 choix, il devra entrer une chaine en boucle j'usqu'a ce qu'ele soit validé
        {
        p=2;
        }else if (strcmp(c_repenigme2,"oreiller")==0) {
        p=2;
        }else if (strcmp(c_repenigme2,"chaise")==0) {
        p=2;
        }else if (strcmp(c_repenigme2,"robinet")==0) {
        p=2;
        }else{

        printf("je n'ai pas compris \n");

        }
    }
    send(server,c_repenigme2,sizeof(c_repenigme2),0);
    printf("Envoye\n");
    system("cls");
    lireFichier("valide_enigme2.txt");
    printf("\n");
    lireFichier("intro_enigme1.txt");

    int notWin = 1;
        if (strcmp(c_repenigme,"elephant")==0)
            {
                printf("Gros, gris et lent, jamais je n'oublie ce que je vois\n");
                scanf("%s",c_rep);
                    if (strcmp(c_rep,"elephant")==0)
                        {
                            printf("Bonne reponse\n");
                            notWin = 0;
                            }else{
                            printf("Mauvaise reponse\n");
                        }

            }else if (strcmp(c_repenigme,"chauve-souris")==0)
            {
                printf("Quand il n'est pas la, je danses, malgré le fait que je n'ai plus de cheuveux");
                scanf("%s",c_rep);
                if (strcmp(c_rep,"chauve-souris")==0)
                        {
                            printf("Bonne reponse\n");
                            notWin = 0;
                            }else{
                            printf("Mauvaise reponse\n");
                        }
            }
            else if (strcmp(c_repenigme,"chat")==0)
 {
                printf("Je passe mon temps a dormir, mais je reste fatigué de vous voir\n");
                scanf("%s",c_rep);
                if (strcmp(c_rep,"chat")==0)
                        {
                            printf("Bonne reponse\n");
                            notWin = 0;
                            }else{
                            printf("Mauvaise reponse\n");
                        }
            }
            else if (strcmp(c_repenigme,"homme")==0)
            {
                printf("J'ai 4 jambes le matin, deux a midi, et trois le soir\n");
                scanf("%s",c_rep);
                if (strcmp(c_rep,"homme")==0)
                        {
                            printf("Bonne reponse\n");
                            notWin = 0;
                            }else{
                            printf("Mauvaise reponse\n");
                        }
            }


    system("cls");
    if (notWin == 1) {
        lireFichier("defaite.txt");
    } else {
        lireFichier("victoire.txt");
    }

    closesocket(server);
    WSACleanup();
    printf("Deconnexion\n");

    return 0;
}

int lireFichier(char *nomFicher) {
  char cText[1024];
  FILE *fSortie=NULL;
  int cursor=0;

  fSortie = fopen(nomFicher,"r");

  fseek(fSortie,0L,SEEK_END);
  int end = ftell(fSortie);
  rewind(fSortie);


  while (cursor < end) {
        fgets(cText,1024,fSortie);
        printf("%s\n",cText);
        cursor = ftell(fSortie);
  }
  return cursor;
}
