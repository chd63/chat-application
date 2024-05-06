#include "main.h"

// contains the detailed code that is kicking off a client - reading properties 
// and then starting the two threads that implement both the sending and the receiving 
// side with respect to the server. This code needs to be fully functional and should 
// only need little tweaking as a result of debugging.


int main(int argc, char *argv[])
   {
    // Check if the user has provided a username as a command-line argument
    if (argc != 3) {
        printf("Usage: %s <username> <port>\n", argv[0]);
        return 1; // Return with an error code
    }

    char username[16];

    strcpy(username, argv[1]);

    unsigned short int port;

    port = (unsigned short int)atoi(argv[2]);


    //uncomment for testing
    printf("Username: %s\n", username);
    printf("Port: %hu\n", port);


    // kick off the client

    // read properies 

    // set the name of the proprty files in a character pointer
    char* properties_file = "test.properties";

    // get the head of the struct for properties
    Properties* head = property_read_properties(properties_file);

    // create a struct to be able to push through both username and head
    ThreadData threadData;
    strcpy(threadData.username, username);
    threadData.head = head;
    threadData.port = port;


    // CREATE TWO THREADS
    pthread_t sendingThread, receivingThread;

    // THREAD 1: SENDING THREAD
       // we are sending to the function sendThread with the pointer to the properties struct
    pthread_create(&sendingThread, NULL, sendThread, (void*)&threadData);

    // THREAD 2: RECEIVING THREAD
       // we are sending to the function receiveThread with the pointer to the properties struct    
    pthread_create(&receivingThread, NULL, receiveThread, (void*)&threadData);


    // join the threads back
    pthread_join(sendingThread, NULL);
    pthread_join(receivingThread, NULL);

    // end 
    return 0;

   }