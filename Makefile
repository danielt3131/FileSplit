SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
TARGET = fsm
LDFLAGS = -lncurses
OBJS = main.o splitfile.o mergefile.o fileSize.o selection.o message.o selectionCLI.o
PREFIX = /usr/local/bin
all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
%.o: src/%.c
	$(CC) $(CFLAGS) -c $<
clean:
	@rm -f $(OBJS) $(TARGET)
run:
	./$(TARGET)
install: $(TARGET)
	@install -D -m 755 $(TARGET) $(PREFIX)/$(TARGET)
	@echo Installed $(TARGET) into $(PREFIX)
uninstall:
	@rm -f $(PREFIX)/$(TARGET)
	@echo Uninstalled $(TARGET) from $(PREFIX)