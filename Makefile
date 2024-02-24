NAME			=	pipex
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g
RM				=	rm -rf

OUT_DIR			=	build
SRCS			=	src/pipex.c src/cmd.c src/thread.c src/utils.c src/error.c
OBJS			=	$(SRCS:%.c=$(OUT_DIR)/%.o)

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

all:				$(NAME)

$(NAME):			$(LIBFT)
					$(CC) $(CFLAGS) -Iincludes -Ilibft -Llibft -lft ${MAIN} $(SRCS) build/libft.a -o $(NAME)

$(LIBFT):			$(OUT_DIR)
					make -C $(LIBFT_PATH) bonus
					cp	$(LIBFT) ./build/libft.a

$(OUT_DIR):
					mkdir -p $(OUT_DIR)

bonus:				all

clean:
					$(RM) $(OUT_DIR)
					make -C $(LIBFT_PATH) clean

fclean:				clean
					$(RM) $(NAME)
					make -C $(LIBFT_PATH) fclean

re:					fclean all

.PHONY:				all clean fclean re bonus
