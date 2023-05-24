/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:26:04 by mmorue            #+#    #+#             */
/*   Updated: 2023/05/24 15:30:55 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <limits.h>
# include "memory_manager/memory_manager.h"
# include "libs/get_next_line/get_next_line.h" 
# include "libs/ft_printf/ft_printf.h" 
# include <signal.h>
# include <errno.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>

// LINK PARSED COMMANDS
typedef struct s_command
{
	int					type;
	void				*cmd;
	struct s_command	*next;
}	t_command;

// LINK ENV VARIABLE
typedef struct s_env
{
	char	*name;
	char	*content;
	int		rank;
	void	*next;
}	t_env;

// LINK COMMANDS EXIT CODE
typedef struct s_cmd_exit
{
	int		exit_code;
	void	*next;
}	t_cmd_exit;

// MAIN STRUCT
typedef struct s_minishell
{
	char		*console;
	char		*path;
	void		*history_cmd;
	char		*actual_dir;
	char		*command;
	t_command	*cmd;
	t_env		*var_env;
	t_cmd_exit	*cmd_exit_code;
}	t_minishell;

// ===== PARSED COMMANDS =====
typedef struct s_redirection
{
	int		type;
	char	*file_name;
	void	*value;
	int		value_type;
	int		error;
	char	*error_msg;
}	t_redirection;

typedef struct s_echo
{
	int				type;
	int				no_brkln;
	char			*value;
	int				printable;
	int				error;
	char			*error_msg;
	t_redirection	*stdin;
}	t_echo;

typedef struct s_export
{
	int				type;
	char			*name;
	char			*content;
	int				egal;
	int				envable;
	int				printable;
	int				error;
	char			*error_msg;
	t_redirection	*stdin;
}	t_export;

typedef struct s_unset
{
	int				type;
	char			*name;
	int				printable;
	int				error;
	char			*error_msg;
	t_redirection	*stdin;
}	t_unset;

typedef struct s_cd
{
	int				type;
	char			*path;
	int				printable;
	int				error;
	char			*error_msg;
	t_redirection	*stdin;
}	t_cd;

typedef struct s_none
{
	int				type;
	int				printable;
	int				error;
	char			*error_msg;
	t_redirection	*stdin;
}	t_none;

typedef struct s_pwd
{
	int				type;
	int				error;
	char			*error_msg;
	t_redirection	*stdin;
}	t_pwd;

typedef struct s_env_
{
	int				type;
	int				printable;
	int				error;
	char			*error_msg;
	t_redirection	*stdin;
}	t_env_;

typedef struct s_exit
{
	int				type;
	char			*code;
	int				printable;
	int				error;
	char			*error_msg;
	t_redirection	*stdin;
}	t_exit;

typedef struct s_exec
{
	int				type;
	char			*cmd_path;
	char			**data;
	int				printable;
	int				error;
	char			*error_msg;
	t_redirection	*stdin;
}	t_exec;

typedef struct s_pipe
{
	int		type;
}	t_pipe;

// ===== UTILS =====
typedef struct s_value_cmd
{
	int			sz;
	int			pose;
	char		*value;
	t_minishell	*main;
}	t_value_cmd;

typedef struct s_cmd_and_main
{
	char		**str;
	t_minishell	*main;
}	t_cmd_and_main;

typedef struct s_raw_builtin
{
	char					chara;
	struct s_raw_builtin	*next;
}	t_raw_builtin;

typedef struct s_builtin
{
	int						type;
	struct s_raw_builtin	*raw;
	struct s_builtin		*next;
}	t_builtin;

typedef struct s_parsed_cmd
{
	int						type;
	struct s_builtin		*cmd;
	struct s_parsed_cmd		*next;
}	t_parsed_cmd;

typedef struct s_pipe_fork
{
	int		**fd;
	int		i;
	char	*out;
	pid_t	*pid;
}	t_pipe_fork;

// ECHO
char			*ft_print_echo(t_echo *echo);

// PWD
char			*get_pwd(void);
char			*get_dir(char *path);
void			ft_changepwd(t_env **env);

// EXPORT
char			*ft_export_exec(t_env **env_lst, t_export *export);
char			*ft_printenv_export(t_env **env);
int				ft_lstsize_env(t_env *lst);
void			ft_setrank(t_env **env);
void			ft_assignrank(int i, int size_lst, t_env *current, t_env *next);
char			*ft_export_set_content(char *content, t_export *exp, int type);
char			*ft_printenv_export_disp(t_env *current, char *env);
void			add_export_manual(t_env **env_lst);

// CD
char			*get_dir_fill(int size, int i, char *path);
char			*ft_cd(t_cd *cd, t_minishell *main);
char			*print_pwd(t_pwd *pwd);

// GENERAL PARSING
char			*env_get_user(t_env **env_lst);

// EXECUTE ENV
t_env			*ft_envnew(char *str);
void			ft_env_add_back(t_env **lst, t_env *new);
char			*ft_get_env_name(char *str);
char			*ft_get_env_content(char *str);
void			env_init(int i, char **argv, t_minishell *main);
int				ft_strcmp(char *s1, char *s2);
t_env			*ft_export_new(t_export *export);
void			ft_export_add_back(t_env **lst, t_env *new);
char			*ft_unset(t_env **env_lst, t_unset *unset);
int				ft_check_if_exist(t_env **env_lst, t_export *export);
char			*ft_get_env(t_env **env_lst, char *name);
char			*ft_printenv(t_env *env);
void			ft_exc_cmd(t_minishell *main);
char			*ft_exec_cdm_follow(t_command *temp, t_minishell *main);
char			*ft_exec_cdm_two(t_command *temp, t_minishell *main);

// CONSOLE
void			ft_get_readln_disp(t_minishell	*main);

// UTILS
int				ft_strlen_(char *str);
char			*ft_strjoin_(char *s1, char *s2);
char			*ft_strdup_(char *str);
long long		ft_atoi_long(const char *str);
char			*ft_strdup_buff(char *str);
char			*ft_strjoin_frees1_buff(char *s1, char *s2);

//EXEC
void			inthandler(int sig);
char			*ft_strjoin_frees1(char *s1, char *s2);
char			**env_fork(t_env *env);
char			*check_path(t_env *env, char *exec);
void			check_to_exec(t_minishell *main, t_exec *exec);
void			exec_path(t_minishell *main, t_exec *exec, char *path);
int				get_exit_code(int input);
int				check_dir_exec(char *path);

//START
void			init_shell(t_minishell	*main, int argc, char **argv);

// UTILS LIST BUILTIN
void			ft_bltnadd_back(t_builtin **lst, t_builtin *new);
t_builtin		*ft_bltnnew(t_raw_builtin *raw, int type);
void			ft_rawadd_back(t_raw_builtin **lst, t_raw_builtin *new);
t_raw_builtin	*ft_rawnnew(char chara);
t_parsed_cmd	*ft_cmndnew(t_builtin *raw, int type);
void			ft_cmndadd_back(t_parsed_cmd **lst, t_parsed_cmd *new);
char			*link_list_to_str(t_raw_builtin *raw, int size);
int				get_link_list_size(t_raw_builtin *raw);

// BUILTIN
int				builtin_end_a(char c);
int				builtin_end_b(char c);
int				ft_builtin_quote(char *str, int i, char c,
					t_builtin **head_bltn);
int				ft_builin_end(char *str, int i, char c, t_builtin **head_bltn);
void			ft_builtin(char *str, t_builtin **head_bltn, int i);

// GET COMMANDS
void			get_cmds(t_parsed_cmd **cmd, t_command **all_cmd,
					t_minishell *main);
char			*get_cmd_type_value(t_builtin *tmp, char *out);
char			*get_cmd_type(t_builtin *tmp);
void			get_exist_cmd(t_builtin *start, char *cmd_name,
					t_command **all_cmd, t_minishell *main);
t_pipe			*add_pipe(void);

// PARSE ECHO
t_echo			*add_echo(int type);
int				parse_echo_if(t_builtin *tmp);
void			parse_echo(t_builtin *start, t_command **all_cmd);
t_builtin		*get_echo_return_line(t_builtin *start, int *brkln);
t_builtin		*get_echo_return_line_2(t_builtin *start, t_raw_builtin *raw,
					t_builtin *tmp, int *brkln);
t_builtin		*get_echo_return_line_3(t_builtin *start, t_raw_builtin *raw,
					int *brkln);
void			parse_echo_error_quote(t_echo *echo, t_builtin *start);
void			parse_echo_error(t_echo *echo, int error, char *error_msg);

// PARSE EXPORT
t_export		*add_export(int type);
void			parse_export_egal(t_export *export, t_raw_builtin **raw,
					t_builtin **tmp);
t_raw_builtin	*parse_export_fill(t_export *export, t_raw_builtin *raw);
void			parse_export_cmd(t_builtin *start, t_command **all_cmd);
void			parse_export(t_builtin *start, t_command **all_cmd);
void			parse_export_error_quote(t_export *export, t_builtin *start);
void			parse_export_error(t_export *export, int error,
					char *error_msg);
void			parse_export_checkformat(t_export *export);
void			parse_export_error_msg(t_export *export);
int				parse_export_is_empty(t_export *export);

// PARSE UNSET
t_unset			*add_unset(int type);
void			parse_unset(t_builtin *start, t_command **all_cmd);
void			parse_unset_error_quote(t_unset *unset, t_builtin *start);
void			parse_unset_error(t_unset *unset, int error, char *error_msg);
void			parse_unset_error_msg(t_unset *unset);
void			parse_unset_checkformat(t_unset *unset);

// PARSE CD
t_cd			*add_cd(int type);
void			parse_cd(t_builtin *start, t_command **all_cmd,
					t_minishell *main);
void			parse_cd_error_quote(t_cd *cd, t_builtin *start);
void			parse_cd_error(t_cd *cd, int error, char *error_msg);

// PARSE EXEC
t_exec			*add_exec(int type);
void			parse_exec(t_builtin *start, t_command **all_cmd);
void			exec_add_flags(t_exec *exec, char *flag);
t_builtin		*get_exec_flags(t_builtin *start, t_exec *exec, int *pose,
					t_command **all_cmd);
t_builtin		*get_exec_flags_3(t_builtin *start, t_exec *exec, int *pose,
					t_command **all_cmd);
t_builtin		*get_exec_flags_2(t_builtin *start, t_exec *exec, int *pose,
					t_command **all_cmd);
t_builtin		*get_exec_argum(t_builtin *start, t_exec *exec,
					t_command **all_cmd);
t_builtin		*get_exec_path(t_builtin *start, t_exec *exec, int *pose);
void			parse_exec_error_quote(t_exec *exec, t_builtin *start);
void			parse_exec_error(t_exec *exec, int error, char *error_msg);
char			*get_exec_argum_str(t_builtin *tmp, char *str, t_exec *exec);

// PARSE PWD AND ENV
t_none			*add_none(int type);
void			parse_unset_cmd(t_builtin *start, t_command **all_cmd);
void			parse_none(t_builtin *start, t_command **all_cmd, int type);
void			parse_none_error_quote(t_none *none, t_builtin *start);
void			parse_none_error(t_none *none, int error, char *error_msg);

// PARSING REDIRECTION
t_builtin		*get_redirection_auto(t_builtin *start, int type,
					void *main_cmd, t_command **all_cmd);
t_redirection	*add_redirection(int val_type, int type, void *main_cmd);
t_builtin		*get_redirection_2(t_builtin *tmp, t_command **all_cmd,
					t_raw_builtin *raw, t_redirection *redi);
t_builtin		*get_redirection_3(t_builtin *tmp, t_command **all_cmd,
					t_raw_builtin *raw, t_redirection *redi);
t_builtin		*get_redirection_out(t_builtin *start, int type, void *main_cmd,
					t_command **all_cmd);
t_builtin		*get_redirection(t_builtin *start, int type, void *main_cmd,
					t_command **all_cmd);
void			redi_printable(int val_type, void *main_cmd);
void			redi_printable_2(int val_type, void *main_cmd);
void			redi_err(int val_type, void *main_cmd, char *err);
void			redi_err_2(int val_type, void *main_cmd, char *err);
t_builtin		*get_redirection_err(int val_type,
					t_raw_builtin *raw, void *main_cmd, char c);
t_builtin		*get_redirection_in(t_builtin *start, int type, void *main_cmd,
					t_command **all_cmd);
t_builtin		*get_redirection_in_separator(t_builtin *start,
					t_command **all_cmd, t_redirection *redi);
t_builtin		*get_redirection_in_file_b(t_builtin *start,
					t_command **all_cmd, t_redirection *redi, int skip);
char			*parse_line(char *line);
char			*get_quote(char *out, int type);
void			ft_builtin_line(char *str, t_builtin **head_bltn, int i);
void			set_stdin(void *main_cmd, t_redirection *redi, int type);

// PARSING BACKSLASH
void			parse_backslash(t_builtin **head_bltn);
void			parse_backslash_noquote(t_builtin *btln);

// PARSING ENV VARIABLE
t_raw_builtin	*unlink_var_key(t_raw_builtin *raw, int size);
t_raw_builtin	*get_parse_env(t_raw_builtin *act, int size, t_minishell *main);
void			get_parse_var(t_builtin *act_bltn, t_raw_builtin *raw,
					t_minishell *mn);
void			parse_var(t_builtin **head_bltn,
					t_minishell *main);
int				get_var_size(t_raw_builtin *raw);
char			*get_var_key(t_raw_builtin *raw, int size);

// PARSING COMMAND 
void			clear_cmd_list(t_builtin *start);
void			parse_cmd(t_builtin **head_bltn, t_parsed_cmd **cmd);
void			parse_cmd_2(t_parsed_cmd **cmd,
					t_builtin **back, t_builtin **tmp);
void			parse_base(t_builtin **head_bltn, t_minishell *main);
void			get_parsed_command(char *str, t_minishell *main);

// PARSING EXIT
void			parse_exit(t_builtin *start, t_command **all_cmd);
t_exit			*add_exit(int type);
void			parse_exit_error(t_exit *exit, int error, char *error_msg);
void			parse_exit_error_quote(t_exit *exit, t_builtin *start);

// PARSING UTILS
char			*ft_strjoin_char(char *s1, char s2);
t_command		*ft_cmdnew(void	*cmd, int type);
void			ft_cmd_add_back(t_command **lst, t_command *new);
t_builtin		*parse_del_one(t_builtin *start);
t_builtin		*parse_skip_one(t_builtin *start);
t_builtin		*parse_skip_space(t_builtin *start);
char			*remove_end_char(char *str, int last);
t_minishell		*get_main(void *input);
void			redirection_by_sep(char *separator, int *fd);
char			*red_by_sep(char *separator, int *fd, pid_t pid);

// EXIT
void			ft_exit(t_exit *exit_code);
int				exit_check_max(char *input, char *long_max);
int				exit_check_size(char *input);
int				exit_check_if_negative(char *input);
int				exit_compare(char *input, char *compare);
int				exit_check_long(char *input);

// ERROR
void			error_msg_exit(char *msg);
void			error_msg_exit_code(char *msg, int code);
void			parse_none_for_err(t_command **all_cmd);

// EXEC CMD UTILS
void			free_command_a(t_command *cmd);
void			free_command_b(t_command *cmd);
int				check_if_valid_command(t_command *start);
void			free_command(t_command *cmd);
void			free_command_all(t_command *start);
int				get_commands_size(t_command *start);
char			*get_commands_type(t_command *start, int size);
t_command		**get_commands_arr(t_command *start, int size);
void			ft_exec_pipe(int nb_command, t_command **pipe_cmd,
					int nbr_pipe);
int				get_signal_status(int input);
int				pipe_check_redi_out(t_command *pipe_cmd);
t_redirection	*pipe_get_last_redirection(t_command *pipe_cmd);
void			ft_stdout_bltn(t_pipe_fork ppfk,
					t_command *pipe_cmd, int nb_command);
void			ft_stdout_exec(int **fdpipe, int i,
					t_command *pipe_cmd, int nb_command);
void			ft_stdin_exec(int **fdpipe, int i, t_exec *exec);
void			pipe_wait(t_pipe_fork ppfk, int nb_command, pid_t *pid);
void			pipe_bltn(t_pipe_fork ppfk, t_command **pipe_cmd,
					int nb_command, t_minishell *main);
void			ft_stdin_exec_fork(int **fdpipe, int i, t_exec *exec, int *fd);
void			pipe_exec(t_pipe_fork ppfk, t_command **pipe_cmd,
					int nb_command, t_minishell *main);
void			pipe_choose(t_pipe_fork ppfk, t_command **pipe_cmd,
					int nb_command, int nbr_pipe);
char			*infinit_join(const char *fmt, ...);
void			ft_close(int **fd, int nb_command);
void			ft_close_specific(int **fd, int nb_command, int pose);
char			*ft_check_type_to_exec(int type, t_command *temp,
					t_minishell *main);
int				ft_check_type(int type);
int				get_nbr_of_pipe(t_command **lst);
char			*pipe_exec_bltn(t_command *pipe_cmd);
void			set_exit_code(int input);
void			pipe_bltn_check_redi(t_command *pipe_cmd);
void			exec_local(t_minishell *main, t_exec *exec, char **a);
void			exec_local_check_cmd(char **a);

// MANAGE FILE
int				get_file_acces(char *path);
void			write_append_file(char *path, char *file_act,
					char *file_append);
void			create_file(char *path, int type);
int				into_file_exec(t_redirection *redi);
int				get_file_acces_exec(char *path);
void			set_file_stdin(char *path);
int				is_dir(char *path);

#endif