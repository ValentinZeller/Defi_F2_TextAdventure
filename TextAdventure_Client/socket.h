#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif


#include <stdio.h>
#include <stdlib.h>
#define PORT 23

void *envoyer(void *sock);

void *recevoir(void *data);
int lireFichier(char *nomFicher);

int login(void);

#endif // SOCKET_H_INCLUDED
