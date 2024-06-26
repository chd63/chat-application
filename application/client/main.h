// includes taken from Wolf Dieter Otte
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <pthread.h>
#include <sys/stat.h>
#include <string.h>

#include "src/properties.h"
#include "src/message.h"
#include "reciever_handler.h"
#include "sender_handler.h"
#include "src/message.h"

// Define the structure
typedef struct {
    char username[16];
    Properties* head;
    unsigned short int port;
} ThreadData;



#define SERVER_ADDRESS "23.254.211.151"   // the server IP
#define PORT 2510                         // randomly decided port

#define NOTE_LENGTH 64  

#define FALSE 0
#define TRUE !FALSE

#define MAX_CONNECTIONS 10