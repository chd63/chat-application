#include "main.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// was having issues putting this struct in the main.h file

typedef struct thread_arg_struct{
    int clientSocket;
    ChatNodes* nodes;
} ThreadArgs;

// Needs to implement the server loop and be able to read properties

int main()
   {
    // initialize variables
    int serverSocket;
    struct sockaddr_in serverAddress;

    // create pointer to name for property file
    char* propertyFile = "test.properties";

    // Create unnamed network socket for server to listen on
    if( (serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
      {
       perror("Error creating socket\n");
       exit(EXIT_FAILURE);
      }

    // get the properties
    Properties* properties = property_read_properties(propertyFile);

    // bind the socket
    
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) 
       {
        perror("setsockopt");
        exit(EXIT_FAILURE);
       }
    

    // accept IP addresses
    serverAddress.sin_family = AF_INET;    

    // accept clients on any interface
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    // uncomment when error checking
    printf("IP address: %s\n", inet_ntoa(serverAddress.sin_addr));

    // set port to listen on
    serverAddress.sin_port = htons(atoi(property_get_property(properties, "serverPort")));

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
    
    // get the information from properties


    // create an empty list of chat nodes
    ChatNodes *nodes = (ChatNodes *)malloc(sizeof(ChatNodes));
    nodes->first = NULL;
    nodes->last = NULL;

    // THE SERVER LOOP
    while ( TRUE )
      {

       //pthread_mutex_lock(&mutex);
  
       printf("Server is running and waiting for connections...\n");
       // accept connection to client
       int clientSocket = accept( serverSocket, NULL, NULL );
       printf("\nServer with PID %d: accepted client\n", getpid());

       // create the args
       ThreadArgs args;

       args.clientSocket = clientSocket;
       args.nodes = nodes;
       

       // create thread to handle the request
       // we are aware that there are race condition
       pthread_t thread;
       if (pthread_create(&thread, NULL, talkToClient, (void *)&args) != 0)
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

       //pthread_mutex_unlock(&mutex);

       
      }
    freeChatNodes(nodes);
    
   }