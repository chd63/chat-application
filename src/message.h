#ifndef message_h
#define message_h

#include "chat_node.h"

// Message Type Identifiers
#define JOIN         1
#define LEAVE        2
#define NOTE         3
#define SHUTDOWN     4
#define SHUTDOWN_ALL 5
#define JOINING      6
#define LEFT         7


// Structure Definitions

typedef char Note[64];

typedef struct message_struct
   {
    unsigned char type;
    ChatNode chat_node;
    Note note;
   } Message;


// Prototypes
void setNoteType( Message note );

#endif