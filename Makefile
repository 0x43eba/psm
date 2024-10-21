CC = gcc
CFLAGS = -Wall -I./include

CLIENT_DIR = src/psm-client
SERVER_DIR = src/psm-server
PSM_DIR = src/psm-standard
BUILD_DIR = build

CLIENT_SRC = $(CLIENT_DIR)/main.c $(CLIENT_DIR)/client.c $(PSM_DIR)/psm.c
SERVER_SRC = $(SERVER_DIR)/main.c $(SERVER_DIR)/server.c $(PSM_DIR)/psm.c
PSM_SRC = $(PSM_DIR)/psm.c

all: client server

client: $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/client $(CLIENT_SRC)

server: $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/server $(SERVER_SRC)

clean:
	rm -f $(BUILD_DIR)/*