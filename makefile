CC = gcc
CFLAGS = -Wall -Iinclude

SRCS = src/main.c src/builtin.c
OBJS = $(SRCS:.c=.o)

TARGET = cshell

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) -o $(TARGET) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJS) $(TARGET)
