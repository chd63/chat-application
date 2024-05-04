#include "main.h"

// here you OUTLINE the code of the function that is being executed in the sending thread. 
// You have to have the main loop in place that processes the different pieces of information 
// a user may input. This, again, involves a code structure with entry points to process the 
// different commands or a note the user put in.

/*

Function: sendThread
Definition: will get the properties from the properties file
will then loop and wait for user input which will determine 
what type of message is sent

*/

// user input loop function
void *sendThread(void  *arg )
   {  
    Properties *headPtr = (Properties *)arg;

    // make sure that we have the server and the port
    printf("Pointer received in sendThread: %p\n", (void *)headPtr);

    // get the server address
    char* server_address = property_get_property(headPtr, "serverIP");

    // comment over when not testing
    printf("This is the server address %s \n", server_address);

    // get the server port number
    char* server_port = property_get_property(headPtr, "serverPort");

    //comment over when not testing
    printf("This is the port number %s\n", server_port);

    // get the users name 
    char* user = property_get_property(headPtr, "clientUsername");

    //comment over when not testing
    printf("This is the user %s\n", user);

    // get the client port
    char* client_port = property_get_property(headPtr, "clientPort");

    //comment over when not testing
    printf("This is the user port %s\n", client_port);

    // get the client ip
    char* client_ip = property_get_property(headPtr, "clientIP");

    //comment over when not testing
    printf("This is the user ip %s\n", client_ip);






    /*
    for testing
    

        char userInput[100];
        unsigned char command;
        Note *note = calloc(NOTE_LENGTH, sizeof(char));

        // we are waiting for user input
        printf("Enter: ");
        fgets(userInput, sizeof(userInput), stdin);

        //printf("This is user input %s\n", userInput);

        // we need get the command and the note from user getMessage
        getMessage(userInput, &command, note);

    */
    


    
    // here we have a loop
    while(true)
       {
        char* endptr;

        char userInput[100];
        unsigned char command;
        Note *note = calloc(NOTE_LENGTH, sizeof(char)); 

        // we are waiting for user input
        printf("Enter: ");
        fgets(userInput, sizeof(userInput), stdin);

        //printf("This is user input %s\n", userInput);

        // we need get the command and the note from user getMessage
        getMessage(userInput, &command, note);


        // let use create a chat node
        ChatNode message;
        message.ip = strtoul(client_ip, &endptr, 10);;
        strcpy(message.name, user);
        message.port = atoi(client_port);

        // make a message
        Message sendMessage;
        sendMessage.type = command;
        strcpy(sendMessage.note, *note);
        sendMessage.chat_node = message;


        // prepare connection for tcp

        


        //once we get user input we go to a switch statment

        switch (command)
           {
            // CASE 1: NOTE
            //         call checker function for join
            //         we are going to send a note to the server
            case NOTE:
                
                break;

            // CASE 2: JOIN
            //         we will send a struct with a join to the server
            case JOIN:
                printf("just want to make sure this is working\n");

                // send a message with a join reqest

                
                break;

            // CASE 3: LEAVE
            //         call checker function for join
            //         send a struct with a leave to the server
            case LEAVE:
                break;
            // CASE 4: SHUTDOWN
            //         call checker function for join
            //         send a struct with a leave
            //         shutdown the client
            case SHUTDOWN:
                break;
            // CASE 4: SHUTDOWN ALL
            //         send struct with SHUTDOWN ALL
            //         client will be taken care of by response
            case SHUTDOWN_ALL:
                break;

           }

        free(note);
       }
    

   }



/*

Function: checkJOIN()
Defintion: This function will check to see if the user has 
already joined the server

*/
bool checkJOIN()
   {

   }


/*

Function: getMessage(char userInput, command, note)
Defintion: This function will take in a userinput and will
return the note and the command 

*/

void getMessage(char userInput[100], unsigned char *command, Note *note)
   {
    char strCommand[100];
    int flag = 0;
    int newCounter = 0;
    

    // get the string to the first space
    int noteIndex = 0;
    for(int index = 0; index < strlen(userInput); index++)
       {

        if(flag == 0)
           {
            // uncomment for error checking
            //printf("%c",userInput[index]);

            strCommand[index] = userInput[index];

            newCounter++;
            if(userInput[index] == ' ')
               {
                flag = 1;
                strCommand[index] = '\0';
               }
           }
        else
           {
            if(noteIndex < NOTE_LENGTH - 1)
               {
                // uncomment for error checking
                //printf("%c",userInput[index]);
                (*note)[noteIndex++] = userInput[index];
               }
            else
               {
                (*note)[noteIndex++] = '\0';
                break;
               }
            
           }
       
       }

    


    // uncomment to test
    //printf("%s",strCommand);
    //printf(" %s\n", *note);

    // check if the string is any of the commands if so set to command

    // JOIN
    if(strcmp(strCommand, "JOIN")  == 0)
       {
        *command = JOIN;
       }
    else if(strcmp(strCommand, "LEAVE")  == 0)
       {
        *command = LEAVE;
       }
    else if(strcmp(strCommand, "SHUTDOWN")  == 0)
       {
        *command = SHUTDOWN;
       }
    else if(strcmp(strCommand, "SHUTDOWN_ALL")  == 0 )
       {
        *command = SHUTDOWN_ALL;
       }
    else if(strcmp(strCommand, "NOTE") == 0 )
       {
        *command = NOTE;
       }

   }