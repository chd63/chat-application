#include "reciever_handler.h"

// here you OUTLINE the code that is being executed in the receiving thread: 
// a function containing the server loop. In addition, you need to have another 
// function in place that is being executed when the server connects in the server 
// loop. You need to put a big switch statement into this latter function with entry 
// points for the different kinds of messages that can be received from the server.

// server loop function called receiveThread gets a Proprties pointer passed in

void *receiveThread(void  *arg )
   {
    
    
    // server loop
     
        // will wait for a responce from the server

        // will call the server connecting function(switch statment function)

   }



// server connecting function (called in server loop)

    // switch statment 
    // we need to check what type of command is put in and 
    // see what we get from the server

    // CASE 1: NOTE

        // just display the NOTE to the user

    // CASE 2: LEAVE

        // display someone has left the server

    // CASE 3: JOIN 

        // display someone has joined the server

    // CASE 4: SHUTDOWN ALL 

        // disaply someone has shutdown the whole server 
        // shutdown the client