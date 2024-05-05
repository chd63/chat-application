#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "main.h"

// Declare any constants or macros specific to the client handler

// Declare function prototypes for functions used in the client handler
void *talkToClient(void *clientSocket);

void receive_message(int socket, Message *message);

void sendToAll(ChatNodes* nodes,  Message *message);

void printNodes(ChatNodes* nodes);

void sendAMessage(Message sendMessage,unsigned int server_address,unsigned short int server_port);

void send_message(int socket, const Message *message);

#endif /* PROPERTIES_H */