CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = server.c client.c
NAME = $(SRC:.c=)

all: $(NAME)

%: %.c
	$(CC) $< -o $@

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all

