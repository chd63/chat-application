#include "main.h"

// contains the detailed code that is kicking off a client - reading properties 
// and then starting the two threads that implement both the sending and the receiving 
// side with respect to the server. This code needs to be fully functional and should 
// only need little tweaking as a result of debugging.


int main()
   {

    // kick off the client

    // read properies 

    // set the name of the proprty files in a character pointer
    char* properties_file = "test.properties";

    // get the head of the struct for properties
    Properties* head = property_read_properties(properties_file);

    // CREATE TWO THREADS
    pthread_t sendingThread, receivingThread;

    // THREAD 1: SENDING THREAD
       // we are sending to the function sendThread with the pointer to the properties struct
    pthread_create(&sendingThread, NULL, sendThread, (void*)head);

    // THREAD 2: RECEIVING THREAD
       // we are sending to the function receiveThread with the pointer to the properties struct    
    pthread_create(&receivingThread, NULL, receiveThread, (void*)head);


    // join the threads back
    pthread_join(sendingThread, NULL);
    pthread_join(receivingThread, NULL);

    // end 
    return 0;

   }