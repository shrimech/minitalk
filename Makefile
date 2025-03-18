CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = server.c client.c
NAME = $(SRC:.c=)

all: $(NAME)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
