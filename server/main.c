#include "main.h"

// Needs to implement the server loop and be able to read properties

int main()
   {
    // initialize variables
    int serverSocket;
    struct sockaddr_in serverAddress;


    // Create unnamed network socket for server to listen on
    if( (serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
      {
       perror("Error creating socket\n");
       exit(EXIT_FAILURE);
      }

    // bind the socket

    // accept IP addresses
    serverAddress.sin_family = AF_INET;    

    // accept clients on any interface
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY)

    // set port to listen on
    serverAddress.sin_port = htons(PORT)

    // binding the socket to port
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

    // THE SERVER LOOP
    while ( TRUE )
      {
       // accept connection to client
       int clientSocket = accept( serverSocket, NULL, NULL );
       printf("\nServer with PID %d: accepted client\n", getpid());

       // create thread to handle the request
       // we are aware that there are race condition
       pthread_t thread;
       if (pthread_create(&thread, NULL, talkToClient, (void *)&clientSocket) != 0)
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
       
      }
    
   }