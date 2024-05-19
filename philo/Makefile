CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=address

SRCS = main.c init.c utils.c parsing.c dinner.c write.c monitor.c ft_atol.c ft_malloc.c ft_pthread.c 

OBJS = $(addprefix obj/, $(SRCS:.c=.o))

NAME = philo

GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

all: obj $(NAME)

obj:
	@mkdir -p obj

obj/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "${GREEN}philo compiled${NC}"

clean:
	@rm -rf obj
	@echo "${RED}object files removed${NC}"

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}philo removed${NC}"

re: fclean all
	@echo "${GREEN}philo recompiled${NC}"