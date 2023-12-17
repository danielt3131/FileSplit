CC = gcc
CFLAGS = -Wall -Wextra
TARGET = program
OBJS = main.o splitfile.o mergefile.o fileSize.o
all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)
%.o: src/%.c
	$(CC) $(CFLAGS) -c $<
clean:
	@rm -f $(OBJS) $(TARGET)
run:
	./$(TARGET)
