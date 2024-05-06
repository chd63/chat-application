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

void removeChatNode(ChatNodes* list, const ChatNode* node)
   {
    ChatNodeListElement *current = list->first;
    ChatNodeListElement *prev = NULL;

    while (current != NULL) {
        if (current->chat_node.ip == node->ip &&
            current->chat_node.port == node->port &&
            strcmp(current->chat_node.name, node->name) == 0) {
            // Found the node to remove
            if (prev == NULL) 
               {
                // If it's the first node
                list->first = current->next;
                if (list->first == NULL) 
                   {
                    // If there's only one node in the list
                    list->last = NULL;
                   }
               } 
            else 
               {
                prev->next = current->next;
                if (current->next == NULL) 
                   {
                    // If it's the last node
                    list->last = prev;
                   }
               }
            // Free the memory of the removed node
            free(current);
            return;
        }
        // Move to the next node
        prev = current;
        current = current->next;
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