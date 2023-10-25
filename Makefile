CC = gcc
RM = rm -rf
NAME = minishell
FLAG = -Wall -Werror -Wextra
SPECIAL_FLAG = -L./readline -lreadline -lhistory

# Source files
FILES :=	main.c \
			srcs/env/init.c \
			srcs/env/show.c \
			srcs/env/findandremove.c \
        	srcs/parser/input.c \
			srcs/parser/compute.c \
			srcs/parser/heredoc.c \
			srcs/parser/convertargs.c \
			srcs/parser/removequotes.c \
			srcs/parser/heredoc_files.c \
			srcs/execution/ms_cd.c \
			srcs/execution/ms_exe.c \
			srcs/execution/ms_pwd.c \
			srcs/execution/ms_env.c \
			srcs/execution/signal.c \
			srcs/execution/ms_exit.c \
			srcs/execution/ms_echo.c \
			srcs/execution/ms_pipe.c \
			srcs/execution/fd_list.c \
			srcs/execution/ms_unset.c \
			srcs/execution/ms_export.c \
			srcs/execution/pipe_utils.c \
			srcs/execution/free_input.c \
			srcs/execution/command_handler.c \
			srcs/tools/ft_atoi.c \
			srcs/tools/ft_itoa.c \
			srcs/tools/ft_split.c \
			srcs/tools/ft_bzero.c \
			srcs/tools/ft_errors.c \
			srcs/tools/ft_strtok.c \
			srcs/tools/ft_strlen.c \
			srcs/tools/ft_strcpy.c \
			srcs/tools/ft_strdup.c \
			srcs/tools/ft_substr.c \
			srcs/tools/ft_calloc.c \
			srcs/tools/ft_strcmp.c \
			srcs/tools/ft_isquote.c \
			srcs/tools/ft_isredir.c \
			srcs/tools/ft_isdigit.c \
			srcs/tools/ft_isalpha.c \
			srcs/tools/ft_strncmp.c \
			srcs/tools/ft_strncat.c \
			srcs/tools/ft_strlcpy.c \
			srcs/tools/ft_strlcat.c \
			srcs/tools/ft_isspace.c \
			srcs/tools/ft_strncpy.c \
			srcs/tools/str_is_int.c \
			srcs/tools/ft_strtok2.c \
			srcs/tools/ft_putstr_fd.c \
			srcs/tools/ft_isvariable.c \
			srcs/tools/get_array_size.c \
			srcs/tools/ft_isin2darray.c \
			srcs/tools/ft_sort2darray.c \
			srcs/tools/ft_copy2darray.c \
			srcs/tools/ft_count2darray.c \
			srcs/tools/ft_insert2darray.c \
			srcs/tools/ft_remove2darray.c \
			srcs/tools/ft_getvariablelen.c \
			srcs/tools/free_double_array.c \
			srcs/tools/ft_iscorrectenvname.c

# Object files
OBJS_DIR := objs
OBJS := $(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))

#---------------------------  Colors & Prompt ---------------------------

CYAN="\033[1;36m"
GREEN="\033[1;32m"
BLACKBCK="\033[40m"
ENDCOLOR="\033[0m"
CLEANING := $(BLACKBCK)$(GREEN)[+] Cleaning Completed$(ENDCOLOR)
SUCCESS := $(BLACKBCK)$(GREEN)[+] $(NAME) Successfully Compiled!$(ENDCOLOR)

#---------------------------  Compilation Main ---------------------------

all: $(OBJS_DIR) $(NAME)

# Create the objs directory and the subdirectory structure if it doesn't exist
$(OBJS_DIR):
	@mkdir -p $(dir $(OBJS))

# Compile source files into object files
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@$(CC) $(FLAG) -c $< -o $@
	@echo $(BLACKBCK)$(CYAN)[-] Compiling: $@$(ENDCOLOR)

# Build the final executable
$(NAME): $(OBJS)
	@$(CC) $(FLAG) $(OBJS) -lncurses -o $(NAME) $(SPECIAL_FLAG)
	@echo $(SUCCESS)


#---------------------------     Cleaning      ---------------------------
clean:
	@$(RM) $(OBJS)
	@echo $(CLEANING)

fclean: clean
	@$(RM) $(NAME) $(OBJS_DIR)

re: fclean all

leaks: $(NAME)
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./$(NAME)

run: $(NAME)
	@echo "$$(cat ./logo)"
	@./$(NAME)

#---------------------------       Phony        ---------------------------
.PHONY: all clean fclean re leaks run
