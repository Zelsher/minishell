NAME			= minishell

INC				= inc/
SRC_DIR			= src/
SRC_PARSE		= parsing/
SRC_HEREDOC		= heredoc/
OBJ_DIR			= obj/
LIBFT			= Libft/libft.a

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -I $(INC)
RM				= rm -f

SRC				=	$(SRC_DIR)main.c \
					$(SRC_DIR)minishell.c \
					$(SRC_DIR)exec.c \
					$(SRC_DIR)ft_free.c \
					$(SRC_DIR)signal.c \
					$(SRC_DIR)envp.c \
					$(SRC_DIR)history.c \
					$(SRC_DIR)$(SRC_PARSE)parse.c \
					$(SRC_DIR)$(SRC_PARSE)parsing_utils.c \
					$(SRC_DIR)$(SRC_PARSE)arg_malloc.c \
					$(SRC_DIR)$(SRC_PARSE)cmd_filler.c \
					$(SRC_DIR)$(SRC_HEREDOC)heredoc.c \
					$(SRC_DIR)$(SRC_HEREDOC)heredoc_utils.c \


OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

G = "\033[32m"
X = "\033[0m"

all: 			$(NAME)

bonus:			$(NAME)

$(NAME): 		$(OBJ) $(LIBFT) $(INC)
				@echo $(G)Compiling [$(SRC)]$(X) 
				@$(CC) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
				@echo $(G)Compiling [$(NAME)]$(X) 

$(LIBFT)	:
				@echo $(G)Compiling [LIBFT]$(X) 
				@make -s -C Libft

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@echo $(G)delete [$(OBJ)]$(X) 
				@$(RM) -r $(OBJ_DIR)
				@make clean -s -C Libft

fclean: 		clean
				@echo $(G)delete [$(NAME)]$(X)	
				@$(RM) $(NAME)
				@echo $(G)delete [LIBFT]$(X)
				@make fclean -s -C Libft

re: 			fclean all

.PHONY: 		all clean fclean re