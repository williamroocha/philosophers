CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread #-g -fsanitize=address

SRCS = main.c init.c utils.c sync.c parsing.c dinner.c write.c monitor.c ft_atol.c ft_malloc.c ft_pthread.c clean.c

OBJS = $(addprefix obj/, $(SRCS:.c=.o))

NAME = philo

GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

.PHONY: all clean fclean re

all: obj $(NAME)

obj:
	@mkdir -p obj

obj/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "${GREEN}philo compiled${NC}"

clean:
	@$(RM) -r obj
	@echo "${RED}object files removed${NC}"

fclean: clean
	@$(RM) $(NAME)
	@echo "${RED}philo removed${NC}"

re: fclean all
	@echo "${GREEN}philo recompiled${NC}"