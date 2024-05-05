#include "main.h"

// here you OUTLINE the code that is being executed in the receiving thread: 
// a function containing the server loop. In addition, you need to have another 
// function in place that is being executed when the server connects in the server 
// loop. You need to put a big switch statement into this latter function with entry 
// points for the different kinds of messages that can be received from the server.

// server loop function called receiveThread gets a Proprties pointer passed in

void *receiveThread(void *arg )
   {
    Properties *headPtr = (Properties *)arg;
    
    int serverSocket;
    struct sockaddr_in serverAddress;

    if( (serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
      {
       perror("Error creating socket\n");
       exit(EXIT_FAILURE);
      }    
    
    serverAddress.sin_family = AF_INET;

    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    // uncomment when error checking
    printf("IP address: %s\n", inet_ntoa(serverAddress.sin_addr));

    serverAddress.sin_port = htons(atoi(property_get_property(headPtr, "clientPort")));


    if (bind( serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress) ) != 0)
      {
       perror("Error binding socket");
       exit(EXIT_FAILURE);
      }

    // listen on the socket
    if (listen( serverSocket, MAX_CONNECTIONS) != 0)
      {
       perror("Error listening on socket");
       exit(EXIT_FAILURE);
      }

    // server loop
    while (TRUE)
       {
        // will wait for a responce from the server
        // accept connection to client
        int clientSocket = accept( serverSocket, NULL, NULL );
        printf("\nServer with PID %d: accepted client\n", getpid());

        pthread_t thread;



       if (pthread_create(&thread, NULL, serverFunction, (void *)&clientSocket) != 0)
         {
          perror("Error creating thread");
          exit(EXIT_FAILURE);
         }

       // detach the thread
       if (pthread_detach(thread) !=0)
         {
          perror("Error detaching thread");
         exit(EXIT_FAILURE);
         }

        // will call the server connecting function(switch statment function)
        

       }
     

   }


// server connecting function (called in server loop)
void *serverFunction(void  *arg)
   { 
    printf(" WE GET INTO HERE \n\n\n\n\n");
    // get the clientSocket
    int clientSocket = *((int *)arg);

    // create a temperary message
    Message *tempMessage;

    // call recive_message
    receive_message(clientSocket, tempMessage);


    // switch statment 
    // we need to check what type of command is put in and 
    // see what we get from the server

    switch (tempMessage->type)
       {

        // CASE 1: NOTE
        case NOTE:

            printf("%s",tempMessage->chat_node.name);
            printf("%s\n",tempMessage->note);

            break;

        // CASE 2: LEAVE
        case LEAVE:

            printf("%s left\n",tempMessage->chat_node.name);
        
            break;

            // display someone has left the server

        // CASE 3: JOIN 
        case JOIN:

            printf("%s joined the chat\n",tempMessage->chat_node.name);

            break;

            // display someone has joined the server

        // CASE 4: SHUTDOWN ALL 

            // disaply someone has shutdown the whole server 
            // shutdown the client
        case SHUTDOWN_ALL:

            printf("%s has shutdown the chat\n",tempMessage->chat_node.name);
            return 0;

            break;
        
       }

   }


// Function to receive a Message struct over TCP
void receive_message(int socket, Message *message) {
    // Receive the serialized data
    char buffer[sizeof(Message)];
    recv(socket, buffer, sizeof(Message), 0);

    // Deserialize the data back into a Message struct
    memcpy(message, buffer, sizeof(Message));
}
