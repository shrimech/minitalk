OBJS_SR			=	server.o
OBJS_CL			=	client.o

NAME_SR			=	server
NAME_CL			=	client
CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -g


all : $(NAME_CL) $(NAME_SR)

$(NAME_CL) :$(OBJS_CL) 
	${CC} ${CFLAGS} ${OBJS_CL} -o ${NAME_CL}
	
$(NAME_SR) : $(LIB) $(OBJS_SR) 
	${CC} ${CFLAGS} ${OBJS_SR} -o ${NAME_SR}
	


clean :
	${RM} ${OBJS_CL} $(OBJS_SR)

fclean : clean
	${RM} ${NAME_CL} $(NAME_SR)

re : fclean all

.SECONDARY: $(OBJS_CL) $(OBJS_SR)

.PHONY: all clean fclean re
