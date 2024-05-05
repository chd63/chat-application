// Declare function prototypes for functions used in the sender_handler
void *sendThread(void  *arg );

void getMessage(char userInput[100], unsigned char *command, Note *note);
void sendAMessage(Message sendMessage,char* server_address,char* server_port);

void send_message(int socket, const Message *message);