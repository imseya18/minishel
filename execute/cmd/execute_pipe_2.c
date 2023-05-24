/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:36:54 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 19:47:48 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_check_redi_out(t_command *pipe_cmd)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = pipe_cmd;
	if (!tmp || !tmp->next)
		return (i);
	tmp = tmp->next;
	while (tmp && tmp->type != 100)
	{
		if (tmp->type == 101 || tmp->type == 102)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_redirection	*pipe_get_last_redirection(t_command *pipe_cmd)
{
	t_redirection	*last;
	t_command		*tmp;

	last = 0;
	tmp = pipe_cmd;
	while (tmp && tmp->type != 100)
	{
		if (tmp->type == 101 || tmp->type == 102)
			last = (t_redirection *)tmp->cmd;
		tmp = tmp->next;
	}
	return (last);
}

void	ft_stdin_exec(int **fdpipe, int i, t_exec *exec)
{
	int		fd[2];
	pid_t	pid;

	if (exec->stdin && exec->stdin->type == 103)
		set_file_stdin(exec->stdin->file_name);
	else if (exec->stdin)
	{
		if (pipe(fd) == -1)
			error_msg_exit("Error: failed to open pipe.");
		pid = fork();
		if (pid == 0)
			ft_stdin_exec_fork(fdpipe, i, exec, fd);
		else
		{
			waitpid(pid, 0, 0);
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		}
	}
	else if (i > 0)
		dup2(fdpipe[i - 1][0], STDIN_FILENO);
}

void	ft_stdout_exec(int **fdpipe, int i, t_command *pipe_cmd, int nb_command)
{
	t_redirection	*last;

	if (pipe_check_redi_out(pipe_cmd) > 0)
	{
		last = pipe_get_last_redirection(pipe_cmd);
		if (get_file_acces_exec(last->file_name) == 1 || last->type == 101)
			create_file(last->file_name, last->type);
		dup2(into_file_exec(last), STDOUT_FILENO);
		if (i < nb_command - 1)
			close(fdpipe[i][1]);
	}
	else if (i < nb_command - 1)
	{
		dup2(fdpipe[i][1], STDOUT_FILENO);
	}
}

void	ft_stdout_bltn(t_pipe_fork ppfk, t_command *pipe_cmd, int nb_command)
{
	t_redirection	*last;

	if (pipe_check_redi_out(pipe_cmd) > 0)
	{
		last = pipe_get_last_redirection(pipe_cmd);
		if (get_file_acces_exec(last->file_name) == 1 || last->type == 101)
			create_file(last->file_name, last->type);
		write(into_file_exec(last), ppfk.out, ft_strlen_(ppfk.out));
		if (ppfk.i < nb_command - 1)
			close(ppfk.fd[ppfk.i][1]);
	}
	else if (ppfk.i < nb_command - 1)
		write(ppfk.fd[ppfk.i][1], ppfk.out, ft_strlen_(ppfk.out));
	else
		ft_printf("%s", ppfk.out);
}
