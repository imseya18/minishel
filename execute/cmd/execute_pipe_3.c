/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:21:51 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 13:57:32 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_stdin_exec_fork(int **fdpipe, int i, t_exec *exec, int *fd)
{
	char	*res;

	close(fd[0]);
	res = exec->stdin->file_name;
	write(fd[1], res, ft_strlen_(res));
	if (i > 0)
		close(fdpipe[i - 1][0]);
	ftm_free_all();
	exit(0);
}

void	pipe_exec(t_pipe_fork ppfk, t_command **pipe_cmd, int nb_command,
	t_minishell *main)
{
	char	**a;
	char	*path;

	a = ((t_exec *)pipe_cmd[ppfk.i]->cmd)->data;
	ft_close_specific(ppfk.fd, nb_command, ppfk.i);
	pipe_bltn_check_redi(pipe_cmd[ppfk.i]);
	ft_stdin_exec(ppfk.fd, ppfk.i, (t_exec *)pipe_cmd[ppfk.i]->cmd);
	ft_stdout_exec(ppfk.fd, ppfk.i, pipe_cmd[ppfk.i], nb_command);
	path = check_path(main->var_env, a[0]);
	if (path != NULL)
		execve(path, a, env_fork(main->var_env));
	else
		exec_local(main, ((t_exec *)pipe_cmd[ppfk.i]->cmd), a);
}

void	pipe_wait(t_pipe_fork ppfk, int nb_command, pid_t *pid)
{
	int	status;

	ft_close(ppfk.fd, nb_command);
	ppfk.i = 0;
	while (ppfk.i < nb_command)
	{
		status = 0;
		waitpid(pid[ppfk.i++], &status, 0);
		get_exit_code(status / 256);
	}
	ftm_free(pid);
	ftm_free(ppfk.fd);
}

void	pipe_bltn(t_pipe_fork ppfk, t_command **pipe_cmd, int nb_command,
	t_minishell *main)
{
	ft_close_specific(ppfk.fd, nb_command, ppfk.i);
	pipe_bltn_check_redi(pipe_cmd[ppfk.i]);
	if (ppfk.i > 0)
		close(ppfk.fd[ppfk.i - 1][0]);
	if (ft_check_type(pipe_cmd[ppfk.i]->type) == 0
		|| (ft_check_type(pipe_cmd[ppfk.i]->type) == 1
			&& nb_command > 1))
	ppfk.out = ft_check_type_to_exec(pipe_cmd[ppfk.i]->type,
				pipe_cmd[ppfk.i], main);
	ft_stdout_bltn(ppfk, pipe_cmd[ppfk.i], nb_command);
	ftm_free_all();
	exit(get_exit_code(1000));
}

void	pipe_choose(t_pipe_fork ppfk, t_command **pipe_cmd, int nb_command,
	int nbr_pipe)
{
	t_minishell	*main;

	main = get_main(0);
	ppfk.out = 0;
	if (nbr_pipe == 0)
		ppfk.out = pipe_exec_bltn(pipe_cmd[ppfk.i]);
	ppfk.pid[ppfk.i] = fork();
	if (ppfk.pid[ppfk.i] == 0)
	{
		rl_catch_signals = 0;
		if (pipe_cmd[ppfk.i]->type == 8)
			pipe_exec(ppfk, pipe_cmd, nb_command, main);
		else
			pipe_bltn(ppfk, pipe_cmd, nb_command, main);
	}
}
