#include "client_handler.h"
#include "message.h"


// switch statement for COMMANDS

// the function is OUTLINED, that is going to implement the code that is being executed 
// in a thread that handles a client request, aka void talk_to_client(void* arg) 
// (don't put that code into main.c). This function needs to have a big switch statement, 
// its entry points pertain to the different kinds of messages a server may receive from a client.

// have a function called talkToClient which takes in a clientSocket and a COMMAND 

    // we need to have a switch for all the commands 

    // case 1: JOIN

        // notify all other clients about a new user being added besides the user itself

    // case 2: LEAVE
   
        // notify all clients that the user has left

    // case 3: NOTE

        // send a note to all other clients in the chat

    // case 4: SHUTDOWN ALL

        // shuts down all clients and the server