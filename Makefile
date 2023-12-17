CC = gcc
CFLAGS = -Wall -Wextra -g -O2
TARGET = fsm
LDFLAGS = -lncurses
OBJS = main.o splitfile.o mergefile.o fileSize.o selection.o message.o
all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
%.o: src/%.c
	$(CC) $(CFLAGS) -c $<
clean:
	@rm -f $(OBJS) $(TARGET)
run:
	./$(TARGET)
