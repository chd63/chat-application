#include "chat_node.h"


// define the structure that represents the identifying information of a chat node, i.e. IP, port 
// and logical name. You will also want to foresee functionality that acts upon chat nodes. One 
// important example is to have code in place that implements linked lists for chat nodes. This 
// code needs to be OUTLINED.

// have code here that will implement the linked list

void addChatNode(ChatNodes* list, ChatNode node)
   {
    // create a newElement
    ChatNodeListElement* newElement = (ChatNodeListElement*)malloc(sizeof(ChatNodeListElement));

    newElement->chat_node = node;
    newElement->next = NULL;

    //check if list if empty if so send both first and last pointers to newElement
    if(list->first == NULL)
       {
        list->first = newElement;
        list->last = newElement;
       }
    else
       {
        list->last->next = newElement;

        list->last = newElement;
       }
   }


void freeChatNodes(ChatNodes* list)
   {
    ChatNodeListElement* current = list->first;

    while(current != NULL)
       {
        ChatNodeListElement* temp = current;
        current = current->next;
        free(temp);
       }
    list->first = NULL;
    list->last = NULL;
   }