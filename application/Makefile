CC = gcc
CFLAGS = -Wall -Wextra

SERVER_SRCDIR = server
CLIENT_SRCDIR = client

server: $(SERVER_SRCDIR)/main.c
	$(CC) $(CFLAGS) $(SERVER_SRCDIR)/client_handler.c $(SERVER_SRCDIR)/chat_node.c $(SERVER_SRCDIR)/message.c $(SERVER_SRCDIR)/properties.c $(SERVER_SRCDIR)/main.c -o server-main

client: $(CLIENT_SRCDIR)/main.c
	$(CC) $(CFLAGS) $(CLIENT_SRCDIR)/receiver_handler.c $(CLIENT_SRCDIR)/sender_handler.c $(CLIENT_SRCDIR)/chat_node.c $(CLIENT_SRCDIR)/message.c $(CLIENT_SRCDIR)/properties.c $(CLIENT_SRCDIR)/main.c -o client-main

clean:
	rm -f server-main client-main