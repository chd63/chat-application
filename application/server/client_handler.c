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

         case LEAVE:

            // need to take the user out of nodes
            removeChatNode(threadArgs->nodes,  &message->chat_node);

            sendToAll(threadArgs->nodes, message);

            break;

         case SHUTDOWN:

            // take user out of nodes
            removeChatNode(threadArgs->nodes,  &message->chat_node);

            // switch message to have leave
            message->type = LEAVE;
         
            sendToAll(threadArgs->nodes, message);

            break;

         case SHUTDOWN_ALL:

            sendToAll(threadArgs->nodes, message);

            // take all users out of nodes
            freeChatNodes(threadArgs->nodes);

            exit(EXIT_SUCCESS);
         

            break;
       }

    printNodes(threadArgs->nodes);
    
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

        if ( strcmp(current->chat_node.name, message->chat_node.name ) != 0 ) 
           {
             //Send the message to the current user
            sendAMessage( *message, current->chat_node.ip , current->chat_node.port);
           }

        current = current->next;
       }
   }


/*

FUNCTION: sendMessage
Description: opens up a socket and sends message to server
then closes that socket

*/
void sendAMessage(Message sendMessage, unsigned int server_address, unsigned short int server_port)
   {

    // Create a socket
    int clientSocket;
    struct sockaddr_in serverAddress;
    
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created\n");

    char *server_address_str = inet_ntoa(*(struct in_addr *)&server_address);

    // Prepare server address structure
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(server_address_str);
    serverAddress.sin_port = server_port;

    // Connect to the server
    printf("Connecting to server...\n");
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");

    // Send the message
    send_message(clientSocket, &sendMessage);

    // Close the socket
    close(clientSocket);
    printf("Socket closed\n");
   }


void send_message(int socket, const Message *message) 
   {

    // Serialize the Message struct into a byte array
    char buffer[sizeof(Message)];
    memcpy(buffer, message, sizeof(Message));

    // Send the serialized data over the TCP connection
    send(socket, buffer, sizeof(Message), 0);
   }