#include "main.h"
//#include "chat_node.h"

// was having issues putting this in the main.h file
typedef struct thread_arg_struct{
    int clientSocket;
    ChatNodes* nodes;
} ThreadArgs;

// switch statement for COMMANDS

// the function is OUTLINED, that is going to implement the code that is being executed 
// in a thread that handles a client request, aka void talk_to_client(void* arg) 
// (don't put that code into main.c). This function needs to have a big switch statement, 
// its entry points pertain to the different kinds of messages a server may receive from a client.

void *talkToClient(void  *arg )
   {
    // get the arguments out of args
    ThreadArgs* threadArgs = (ThreadArgs*)arg;

    int clientSocket = threadArgs->clientSocket;
    ChatNodes* nodes = threadArgs->nodes;

    //printf("we are talking to client \n");

    Message *message = (Message *)malloc(sizeof(Message));

    receive_message(clientSocket, message);

    // uncomment for testing of chat nodes
    printNodes(nodes);


    
    //uncomment for testing

    /*

    printf("Type: %u\n", message->type);
    printf("Chat Node IP: %u\n", message->chat_node.ip);
    printf("Chat Node Port: %hu\n", message->chat_node.port);
    printf("Chat Node Name: %s\n", message->chat_node.name);
    printf("Note: %s\n", message->note);

    */


    // switch statment to choose what will occur
    switch (message->type)
       {
        case JOIN:
            // need to add the chat node to the list
            addChatNode(threadArgs->nodes, message->chat_node);

            // need to send out a message to everyone that you joined
            sendToAll(threadArgs->nodes, message);
            break; 

        case NOTE:

            sendToAll(threadArgs->nodes, message);
      
            break;
       }



    
    /*
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
    */
      
    free(message);
   }


// Function to receive a Message struct over TCP
void receive_message(int socket, Message *message) {
    // Receive the serialized data
    char buffer[sizeof(Message)];
    recv(socket, buffer, sizeof(Message), 0);

    // Deserialize the data back into a Message struct
    memcpy(message, buffer, sizeof(Message));
}


/*

function: printNodes(ChatNodes* nodes)
definition: is used to print out all nodes for testing

*/

void printNodes(ChatNodes* nodes)
   {
    ChatNodeListElement* current = nodes->first;

    printf("Nodes:\n");
    while (current != NULL) {
        printf("IP: %u\n", current->chat_node.ip);
        printf("Port: %hu\n", current->chat_node.port);
        printf("Name: %s\n", current->chat_node.name);

        current = current->next;
    }

   }


/*

function: sendToAll
definition: send out the message to all other users

*/   

void sendToAll(ChatNodes* nodes,  Message *message)
   {
    // create a current chantnode
    ChatNodeListElement* current = nodes->first;

    // need to loop through all of the users besides the user sending
    while (current != NULL)
       {
        //uncomment for error checking
        printf("Server IP: %u\n", current->chat_node.ip);
        printf("Server Port: %hu\n", current->chat_node.port);

        

        // we should check what user it is 
        sendAMessage( *message, current->chat_node.ip , current->chat_node.port);

        current = current->next;
       }
   }


/*

FUNCTION: sendMessage
Description: opens up a socket and sends message to server
then closes that socket

*/

void sendAMessage(Message sendMessage,unsigned int server_address,unsigned short int  server_port)
   {
    // prepare connection for tcp
    // this is getting `tested

    int clientSocket;
    struct sockaddr_in serverAddress;

    // create a socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
       {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
       }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = server_address;
    serverAddress.sin_port = server_port;

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) 
       {
        perror("connect failed");
        exit(EXIT_FAILURE);
       }

    printf("Connected to server\n");

    send_message(clientSocket, &sendMessage);


    // end of connecting to tpc
    close(clientSocket);   

   }


void send_message(int socket, const Message *message) {
    // Serialize the Message struct into a byte array
    char buffer[sizeof(Message)];
    memcpy(buffer, message, sizeof(Message));

    // Send the serialized data over the TCP connection
    send(socket, buffer, sizeof(Message), 0);
}