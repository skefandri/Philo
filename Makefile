NAME = philo

BONUS = philo_bonus

CFLAGS = -Wextra -Werror -Wall -I includes -I bonus -I includes -fsanitize=thread

SRCS_MAND = ./philo_man/philosopher.c ./utils/ft_atoi.c ./philo_man/philosopher_actions.c ./src/ft_check.c\

SRCS_BON = ./philoo_bonus/action_bonus.c ./philoo_bonus/check_init.c ./philoo_bonus/philo_bonus.c ./src/ft_check.c ./utils/ft_atoi.c \

all : $(NAME)

$(NAME) : $(SRCS_MAND)
		cc $(CFLAGS) $(SRCS_MAND) -o $(NAME)
bonus : $(BONUS)

$(BONUS) : $(SRCS_BON)
	cc $(CFLAGS) $(SRCS_BON) -o $(BONUS)

clean :
		rm -rf $(OBJS) $(BON_OBJS)
		
fclean : clean
		rm -rf $(NAME) $(BONUS)

re : fclean all
