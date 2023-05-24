LIBFT = libs/ft_printf/libftprintf.a

NAMES = minishell

SOURCES =	main.c\
			libs/get_next_line/get_next_line.c\
			libs/get_next_line/get_next_line_2.c\
			memory_manager/memory_manager.c\
			memory_manager/memory_manager_2.c\
			memory_manager/memory_manager_utils.c\
			manage_file/file.c\
			manage_file/file_2.c\
			execute/error.c\
			execute/cmd/execute_cmd.c\
			execute/cmd/execute_cmd_2.c\
			execute/cmd/execute_cmd_3.c\
			execute/cmd/execute_cmd_4.c\
			execute/cmd/execute_free.c\
			execute/cmd/execute_pipe.c\
			execute/cmd/execute_pipe_2.c\
			execute/cmd/execute_pipe_3.c\
			execute/cmd/execute_pipe_4.c\
			execute/cmd/cd.c\
			execute/cmd/pwd.c\
			execute/env/env_utils.c\
			execute/env/env_utils_2.c\
			execute/env/export.c\
			execute/env/export_2.c\
			execute/env/export_3.c\
			execute/env/unset.c\
			execute/env/exec_utils.c\
			execute/env/exec_utils_2.c\
			execute/redirection/redirection_utils.c\
			builtin/builtin.c\
			builtin/builtin_list.c\
			builtin/builtin_list_2.c\
			builtin/builtin_end.c\
			builtin/link_list_utils.c\
			builtin/get_commands.c\
			parsing/parse_base.c\
			parsing/parse_backslash.c\
			parsing/parse_var.c\
			parsing/parse_var_2.c\
			parsing/parse_command.c\
			parsing/parse_echo.c\
			parsing/parse_echo_2.c\
			parsing/parse_echo_3.c\
			parsing/parse_export.c\
			parsing/parse_export_2.c\
			parsing/parse_cd.c\
			parsing/parse_cd_2.c\
			parsing/parse_none.c\
			parsing/parse_none_2.c\
			parsing/parse_unset.c\
			parsing/parse_unset_2.c\
			parsing/parse_exec.c\
			parsing/parse_exec_2.c\
			parsing/parse_exec_3.c\
			parsing/parse_exit.c\
			parsing/parse_exit_2.c\
			parsing/parse_auto_redi.c\
			parsing/parse_redirection.c\
			parsing/parse_redirection_2.c\
			parsing/parse_in_redirection.c\
			parsing/parse_in_redirection_2.c\
			parsing/parse_in_redirection_3.c\
			parsing/parse_utils.c\
			parsing/parse_utils_2.c\
			parsing/parse_main_get.c\
			parsing/parse_pipe.c\
			utils/utils_1.c\
			utils/utils_2.c\
			utils/atoi_long.c\
			utils/infinit_join.c\


OBJECTS = $(SOURCES:.c=.o)

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g
CC = gcc $(FLAGS)

.c.o:
	@$(CC) -c $(FLAGS) -I /Users/$$USER/.brew/opt/readline/include -I includes $< -o $(<:.c=.o)
all: $(NAMES)

clean:
	rm -f $(OBJECTS)
	$(MAKE) clean -C ./libs/ft_printf

fclean: clean
	rm -f $(NAMES)
	$(MAKE) fclean -C ./libs/ft_printf

re: clean all

$(NAMES):	$(SOURCES) $(OBJECTS)
			$(MAKE) -C ./libs/ft_printf
			$(CC) $(OBJECTS) $(LIBFT) -lreadline -L /Users/$$USER/.brew/opt/readline/lib -o $(NAMES)
