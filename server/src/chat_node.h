#ifndef chat_node_h
#define chat_node_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ChatNode
typedef struct chat_node_struct
   {
    unsigned int ip;
    unsigned short int port;
    char name[16];
   } ChatNode;

// ChatNodeListElement
typedef struct chat_node_list_element_struct
   {
    ChatNode chat_node;
    struct chat_node_list_element_struct* next;
   } ChatNodeListElement;

// ChatNode List
typedef struct chat_node_list_struct
   {
    ChatNodeListElement* first;
    ChatNodeListElement* last;
   } ChatNodes;



#endif