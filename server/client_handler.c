#include "client_handler.h"
#include "message.h"

// switch statement for COMMANDS

// the function is OUTLINED, that is going to implement the code that is being executed 
// in a thread that handles a client request, aka void talk_to_client(void* arg) 
// (don't put that code into main.c). This function needs to have a big switch statement, 
// its entry points pertain to the different kinds of messages a server may receive from a client.

void talkToClient( clientSocket )
   {
    

    switch( message.type )
      {
       // ----------------------------
       case JOIN: 
       // ----------------------------
         {
          int socket_to_chat_node;
          struct affrinfo hints, *server_info;
          int error;
          char portStr[6];

          // protect access to node list
          pthread_mutex_lock( &mutex_chat_node_list );
            {
             // set the type
             message.type = JOINING;

             ChatNodeListElement* current = chat_nodes->first;

             // run through all nodes
             while (current->next)
               {
                // set info to send note to chat_node
                memset(&hints, 0, sizeof(hints));
                hints.ai_socktype = SOCK_STREAM;
                hints.ai_family = AF_INET;
                sprintf(portStr, "%u", current->chat_node.port);

               }
            }
         }
      }
   }