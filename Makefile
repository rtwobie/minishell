# config
NAME		:= minishell
CC			:= cc
SRC_DIR		:= src
OBJ_DIR		:= obj
LIBFT_DIR	:= libft
LIBFT		:= libft.a

CFLAGS	:=
CFLAGS	+= -O2
CFLAGS	+= -Wall
CFLAGS	+= -Wextra
CFLAGS	+= -Werror
CFLAGS	+= -Wno-unused-result
CFLAGS	+= -pedantic
CFLAGS	+= -Wconversion
CFLAGS	+= $(ADDFLAGS)

CPPFLAGS	:=
CPPFLAGS	+= -I$(LIBFT_DIR)
CPPFLAGS	+= -I$(SRC_DIR)

#********** Add the path to your headers here ***********#
# e.g: CPPFLAGS	+= -I$(SRC_DIR)/module/path


CPPFLAGS	+= -I$(SRC_DIR)/run
CPPFLAGS	+= -I$(SRC_DIR)/tokenizer
CPPFLAGS	+= -I$(SRC_DIR)/heredoc
CPPFLAGS	+= -I$(SRC_DIR)/parser
CPPFLAGS	+= -I$(SRC_DIR)/envvar
CPPFLAGS	+= -I$(SRC_DIR)/executor
CPPFLAGS	+= -I$(SRC_DIR)/builtin
CPPFLAGS	+= -I$(SRC_DIR)/error
CPPFLAGS	+= -I$(SRC_DIR)/debug


#********************************************************#

LDFLAGS	:=
LDFLAGS += -L$(LIBFT_DIR)


LDLIBS	:=
LDLIBS	+= -lreadline
LDLIBS	+= -lft
# LDLIBS	+= -lncurses
# LDLIBS	+= -ltermcap

ifeq ($(DEBUG), 1)
	CFLAGS	+= -ggdb3 -O0
	LDFLAGS	+= -ggdb3 -O0
endif

ifeq ($(TSAN), 1)
	CFLAGS	+= -fsanitize=thread
	LDFLAGS	+= -fsanitize=thread
endif

ifeq ($(LSAN), 1)
	CFLAGS	+= -fsanitize=leak
	LDFLAGS	+= -fsanitize=leak
endif

ifeq ($(ASAN), 1)
	CFLAGS	+= -fsanitize=address
	LDFLAGS	+= -fsanitize=address
endif



#******* Add your module and your .c files here ********#
# e.g: vpath %.c $(SRC_DIR)/module/path


# Sources
SRC		:=

vpath %.c $(SRC_DIR)
SRC		+= main.c

vpath %.c $(SRC_DIR)/debug
SRC		+= debug_token.c
SRC		+= debug_ast.c

vpath %.c $(SRC_DIR)/error
SRC		+= error.c

vpath %.c $(SRC_DIR)/run
SRC		+= run.c

vpath %.c $(SRC_DIR)/tokenizer
SRC		+= lexer.c
SRC		+= lexer_utils.c
SRC		+= expander.c
SRC		+= token.c
SRC		+= token_list.c

vpath %.c $(SRC_DIR)/heredoc
SRC		+= heredoc.c

vpath %.c $(SRC_DIR)/parser
SRC		+= ast.c
SRC		+= cleanup.c
SRC		+= parser.c

vpath %.c $(SRC_DIR)/executor
SRC		+= executor.c
SRC		+= redirect.c
SRC		+= search_program.c


#new envvar

vpath %.c $(SRC_DIR)/envvar
SRC		+= envvar.c

vpath %.c $(SRC_DIR)/builtin
SRC		+= exit.c

#*******************************************************#

OBJ		:= $(SRC:.c=.o)
OBJ		:= $(addprefix $(OBJ_DIR)/, $(OBJ))

all: $(NAME)

$(LIBFT_DIR)/$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_DIR)/$(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re:
	@make fclean
	@make all

valtest:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) $(ARGS)

.PHONY: all clean fclean re
.PHONY: valtest
