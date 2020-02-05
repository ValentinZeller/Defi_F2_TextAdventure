#include "socket.h"

int login()
{
    WSADATA WSAData;

    SOCKET server, client;

    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);

    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);

    showHost();
    printf("En attente de connexion de l'autre joueur...\n");

    int clientAddrSize = sizeof(clientAddr);
    int notWin = 1;


    if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {

        printf("Joueur bien connecté!\n");
        system("cls");

        lireFichier("intro_enigme1.txt");

        char c_repenigme[20]; // chaine a envoyé a l'autre pc
        int p = 1;
        while (p == 1) {
            printf("elephant, chauve-souris, chat, homme. \n"); // les 4 choix
            scanf("%s",c_repenigme);
            if (strcmp(c_repenigme,"elephant")==0)// si le joueur entre une autre chaines que les 4 choix, il devra entrer une chaine en boucle j'usqu'a ce qu'ele soit validé
                {
                    p=2;
                }else if (strcmp(c_repenigme,"chauve-souris")==0) {
                    p=2;
                }else if (strcmp(c_repenigme,"chat")==0) {
                    p=2;
                }else if (strcmp(c_repenigme,"homme")==0) {
                    p=2;
                }else{
                    printf("je n'ai pas compris \n");
                }
        }
        send(client,c_repenigme,sizeof(c_repenigme),0);
        system("cls");



        char c_repenigme2[20]; // change en fonction du choix du premier joueur
        char c_rep2[20];
        int reception = 1;
        lireFichier("valide_enigme1.txt");

        printf("\nAttendez l'autre joueur\n");
        while (reception) {
            if (recv(client,c_repenigme2,sizeof(c_repenigme),0) < 0) {
                return 1;
            }
            if (c_repenigme2[0]) {
                reception = 0;
            }
        }
        system("cls");
        lireFichier("intro_enigme2.txt");

        if (strcmp(c_repenigme2,"oignon")==0)
            {
                printf("Que dis un oignon quand il a mal ?\n");
                scanf("%s",c_rep2);
                    if (strcmp(c_rep2,"ail")==0)
                    {
                        printf("Bonne reponse\n");
                        notWin = 0;
                    }else{
                        printf("Mauvaise reponse\n");
                    }

            }else if (strcmp(c_repenigme2,"oreiller")==0)
            {
                printf("Quel est le futur de bailler ?\n");
                scanf("%s",c_rep2);
                if (strcmp(c_rep2,"dormir")==0)
                {
                    printf("Bonne reponse\n");
                    notWin = 0;
                }else{
                    printf("Mauvaise reponse\n");
                }
            }
            else if (strcmp(c_repenigme2,"chaise")==0)
{
                printf("J'ai un dos et des pieds, mais je ne peux pas marcher.Qui suis-je ?\n");
                scanf("%s",c_rep2);
                if (strcmp(c_rep2,"chaise")==0)
                {
                    printf("Bonne reponse\n");
                    notWin = 0;
                }else{
                    printf("Mauvaise reponse\n");
                }
            }
            else if (strcmp(c_repenigme2,"robinet")==0)
            {
                printf("Qu’est-ce qui pleur quand on lui tourne la tete ?\n");
                scanf("%s",c_rep2);
                if (strcmp(c_rep2,"robinet")==0)
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


        closesocket(client);
        printf("Deconnexion.\n");
    }

    return 0;
}


void showHost() {
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    printf("Hostname: %s\n", hostname);
    struct hostent* remoteHost;
    remoteHost = gethostbyname(hostname);
    char* ip;
    ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
    printf("IP address is: %s.\n", ip);
}

int lireFichier(char *nomFicher) {
  char cText[TAILLE];
  FILE *fSortie=NULL;
  int cursor=0;

  fSortie = fopen(nomFicher,"r");

  fseek(fSortie,0L,SEEK_END);
  int end = ftell(fSortie);
  rewind(fSortie);


  while (cursor < end) {
        fgets(cText,TAILLE,fSortie);
        printf("%s\n",cText);
        cursor = ftell(fSortie);
  }
  return cursor;
}

