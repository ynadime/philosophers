NAME = philo

SRC = philosophers.c \
	  init.c \
	  simulation.c \
	  routine.c \
	  utils.c \
	  mem_utils.c \
	  
OBJS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

LDFLAGS = -lreadline

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re