
// Declare function prototypes for functions used in the reciever_handler
void *receiveThread(void  *arg );
void receive_message(int socket, Message *message);

void *serverFunction(void  *arg);