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

    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) 
       {
        perror("setsockopt");
        exit(EXIT_FAILURE);
       }
    
    
    serverAddress.sin_family = AF_INET;

    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);



    // uncomment when error checking
    printf("IP address: %s\n", inet_ntoa(serverAddress.sin_addr));

    // set port to listen on
    //serverAddress.sin_port = htons(9090);

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
        //printf("\nWaiting for connections\n");
        // will wait for a responce from the server
        // accept connection to client
        int clientSocket = accept( serverSocket, NULL, NULL );

        //pthread_t thread;

        serverFunction(&clientSocket);


       /*
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
        */
        

       }
     

   }


// server connecting function (called in server loop)
void serverFunction(void  *arg)
   { 
    // get the clientSocket
    int clientSocket = *((int *)arg);

    // create a temperary message
    Message *tempMessage = allocate_message();


    // call recive_message
    receive_message(clientSocket, tempMessage);


    // switch statment 
    // we need to check what type of command is put in and 
    // see what we get from the server

    switch (tempMessage->type)
       {

        // CASE 1: NOTE
        case NOTE:

            printf("\033[0;31m%s\033[0m:",tempMessage->chat_node.name);
            printf("%s",tempMessage->note);

            break;

        // CASE 2: LEAVE
        case LEAVE:

            // display someone has left the server

            printf("\033[0;31m%s\033[0m: left",tempMessage->chat_node.name);
        
            break;


        // CASE 3: JOIN 
        case JOIN:

            // display someone has joined the server

            printf("\033[0;31m%s\033[0m: joined the chat",tempMessage->chat_node.name);

            break;


        // CASE 4: SHUTDOWN ALL 

        case SHUTDOWN_ALL:

            // disaply someone has shutdown the whole server 

            printf("\033[0;31m%s\033[0m: has shutdown the chat",tempMessage->chat_node.name);
            exit(EXIT_SUCCESS);

            break;
        
       }
    free(tempMessage);

   }


// Function to receive a Message struct over TCP
void receive_message(int socket, Message *message) {
    // Receive the serialized data
    char buffer[sizeof(Message)];
    recv(socket, buffer, sizeof(Message), 0);

    // Deserialize the data back into a Message struct
    memcpy(message, buffer, sizeof(Message));
}

Message* allocate_message() {
    // Allocate memory for the Message structure
    Message *msg = (Message*)malloc(sizeof(Message));
    if (msg == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    // Initialize the allocated memory (optional, depending on your requirements)
    // You can initialize the members of the Message structure if necessary
    return msg;
}
