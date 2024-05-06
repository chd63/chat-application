#include "main.h"
#include <stdint.h>

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
    // flag for join
    int flag = 0;

    ThreadData *threadData = (ThreadData*)arg;
    Properties *headPtr = threadData->head;
    char *username = threadData->username;
    unsigned short int port = threadData->port;



    // make sure that we have the server and the port
    //printf("Pointer received in sendThread: %p\n", (void *)headPtr);

    // get the server address
    char* server_address = property_get_property(headPtr, "serverIP");

    // comment over when not testing
    //printf("This is the server address %s \n", server_address);

    // get the server port number
    char* server_port = property_get_property(headPtr, "serverPort");

    //comment over when not testing
    //printf("This is the port number %s\n", server_port);

    // get the users name 
    char* user = property_get_property(headPtr, "clientUsername");

    //comment over when not testing
    //printf("This is the user %s\n", user);

    // get the client port
    char* client_port = property_get_property(headPtr, "clientPort");

    //comment over when not testing
    //printf("This is the user port %s\n", client_port);

    // get the client ip
    char* client_ip = property_get_property(headPtr, "clientIP");

    //comment over when not testing
    //printf("This is the user ip %s\n", client_ip);


   printf("NOTE: FOR EACH COMMAND YOU USE MAKE SURE TO HAVE A SPACE AFTER THE COMMAND\n");
    
    
    // here we have a loop
    while(true)
       {
        char* endptr;

        char userInput[100];
        unsigned char command;
        Note *note = calloc(NOTE_LENGTH, sizeof(char)); 

        // we are waiting for user input
        //printf("\033[0;31m%s\033[0m:",username);
        fgets(userInput, sizeof(userInput), stdin);

        //printf("This is user input %s\n", userInput);

        // we need get the command and the note from user getMessage
        getMessage(userInput, &command, note);

        //printf("This is the user ip %s\n", client_ip);

        // get an unsined int
        uint32_t ip_int = inet_addr(client_ip);

        // let use create a chat node
        ChatNode message;
        message.ip = ip_int;
        strcpy(message.name, username);
        message.port = port;


        // make a message
        Message sendMessage;
        sendMessage.type = command;
        strcpy(sendMessage.note, *note);
        sendMessage.chat_node = message;



        //once we get user input we go to a switch statment

        switch (command)
           {
            // CASE 1: NOTE
            //         call checker function for join
            //         we are going to send a note to the server
            case NOTE:
                if(flag == 1)
                   {
                    // send the note 
                    sendAMessage(sendMessage,server_address, server_port);

                   }
                else
                   {
                    printf("ERROR: YOU HAVE NOT JOINED THE SERVER YET\n"); 
                   }
                
                break;

            // CASE 2: JOIN
            //         we will send a struct with a join to the server
            case JOIN:

                if(flag == 0)
                   {
                    // we will join
                    sendAMessage(sendMessage,server_address, server_port);

                    flag = 1;
                   }
                else
                   {
                    printf("ERROR: YOU HAVE ALREADY JOINED THE SERVER\n"); 
                   }

                
                break;

            // CASE 3: LEAVE
            //         call checker function for join
            //         send a struct with a leave to the server
            case LEAVE:

                if(flag == 1)
                   {
                    // leave the server
                    sendAMessage(sendMessage,server_address, server_port);

                    flag = 0;
                   }
                else
                   {
                    printf("ERROR: YOU HAVE NOTE YET JOINED THE SERVER\n"); 
                   }
                break;

            // CASE 4: SHUTDOWN
            //         call checker function for join
            //         send a struct with a leave
            //         shutdown the client
            case SHUTDOWN:
                if(flag == 1)
                   {
                    // leave the server
                    sendAMessage(sendMessage,server_address, server_port);

                    // make sure to shutdown the application
                    exit(EXIT_SUCCESS);

                   }
                else
                   {
                    printf("ERROR: YOU HAVE NOTE YET JOINED THE SERVER\n"); 
                   }
                break;
            // CASE 4: SHUTDOWN ALL
            //         send struct with SHUTDOWN ALL
            //         client will be taken care of by response
            case SHUTDOWN_ALL:
                if(flag == 1)
                   {
                    // leave the server
                    sendAMessage(sendMessage,server_address, server_port);

                    // make sure to shutdown the application
                    exit(EXIT_SUCCESS);

                   }
                else
                   {
                    printf("ERROR: YOU HAVE NOTE YET JOINED THE SERVER\n"); 
                   }
                break;
            default:
                printf("ERROR: NO COMMAND INPUT\n"); 
                break;

           }

        free(note);
        //free(message);
        //free(sendMessage);
       }
    

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

    // check to see if string is a command


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
    else 
       {
        *command = NOTE;

        char temp[64];

        strcpy(temp, strCommand);

        strcat(temp, " ");

        strcat(temp, *note);

        strcpy(*note, temp);

       }

   }

/*

FUNCTION: sendMessage
Description: opens up a socket and sends message to server
then closes that socket

*/

void sendAMessage(Message sendMessage,char *server_address,char *server_port)
   {
    // prepare connection for tcp
    // this is getting `tested

    int clientSocket;
    struct sockaddr_in serverAddress;

    // create a socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
       {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
       }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(server_address);
    serverAddress.sin_port = htons(atoi(server_port));

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) 
       {
        perror("connect failed");
        exit(EXIT_FAILURE);
       }


    send_message(clientSocket, &sendMessage);



    // end of connecting to tpc
    close(clientSocket);

   }


/*

FUNCTION: send_message
DEFINITION: will send a message to the server

*/


void send_message(int socket, const Message *message) 
   {
    // Serialize the Message struct into a byte array
    char buffer[sizeof(Message)];
    memcpy(buffer, message, sizeof(Message));

    // Send the serialized data over the TCP connection
    send(socket, buffer, sizeof(Message), 0);
   }


uint32_t ip_to_int(const char *ip_address) {
    struct in_addr addr;
    if (inet_pton(AF_INET, ip_address, &addr) == 1) {
        return ntohl(addr.s_addr);
    } else {
        // Error handling for invalid IP address
        return 0;
    }
}