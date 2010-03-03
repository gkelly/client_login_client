# Copyright 2010 Garret Kelly, All Rights Reserved
# Author: gkelly@gkelly.org (Garret Kelly)

SHARED_TARGET = libclient_login_client.so
STATIC_TARGET = libclient_login_client.a

SRC = client_login_client.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -fPIC

.PHONY: all clean

all: $(SHARED_TARGET) $(STATIC_TARGET)

clean:
	rm -f $(SHARED_TARGET) $(STATIC_TARGET) $(OBJ)

$(SHARED_TARGET): $(OBJ)
	$(CC) -shared $(OBJ) -o $(SHARED_TARGET)

$(STATIC_TARGET): $(OBJ)
	$(AR) rcs $(STATIC_TARGET) $(OBJ)
