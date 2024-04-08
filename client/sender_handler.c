#include "sender_handler.h"

// here you OUTLINE the code of the function that is being executed in the sending thread. 
// You have to have the main loop in place that processes the different pieces of information 
// a user may input. This, again, involves a code structure with entry points to process the 
// different commands or a note the user put in.

// user input loop function

    // here we have a loop

        // we are waiting for user input


        //once we get user input we go to a switch statment

        // CASE 1: NOTE
            // call checker function for join
            // we are going to send a note to the server

        // CASE 2: JOIN
            // we will send a struct with a join to the server

        // CASE 3: LEAVE
            // call checker function for join
            // send a struct with a leave to the server

        // CASE 4: SHUTDOWN
            // call checker function for join
            // send a struct with a leave
            // shutdown the client

        // CASE 4: SHUTDOWN ALL
            // send struct with SHUTDOWN ALL
            // client will be taken care of by responce


// checker function for join
    // return true if already joined on server