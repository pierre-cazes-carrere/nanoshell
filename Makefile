CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -I./include
LDFLAGS = 

SRCS = src/main.c src/prompt.c src/parser.c src/exec.c src/builtins.c
OBJS = $(SRCS:.c=.o)
TARGET = nanoshell

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
