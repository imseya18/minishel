/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:58:30 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 15:28:24 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_close_specific(int **fd, int nb_command, int pose)
{
	int	i;

	i = 0;
	while (i < nb_command - 1)
	{
		if (i + 1 != pose)
			close(fd[i][0]);
		if (i != pose)
			close(fd[i][1]);
		i++;
	}
}	

void	ft_close(int **fd, int nb_command)
{
	int	i;

	i = 0;
	while (i < nb_command - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

char	*ft_check_type_to_exec(int type, t_command *temp, t_minishell *main)
{
	if (type == 2 || type == 4 || type == 5 || type == 7)
		return (ft_exec_cdm_two(temp, main));
	else
		return (ft_exec_cdm_follow(temp, main));
}

int	ft_check_type(int type)
{
	if (type == 2 || type == 4 || type == 5 || type == 7)
		return (1);
	else
		return (0);
}

void	ft_exec_pipe(int nb_command, t_command **pipe_cmd, int nbr_pipe)
{
	pid_t		*pid;
	t_pipe_fork	ppfk;

	pid = ftm_malloc((nb_command) * sizeof(pid_t));
	ppfk.fd = ftm_malloc((nb_command - 1) * sizeof(int *));
	ppfk.i = 0;
	ppfk.out = 0;
	while (ppfk.i < nb_command -1)
	{
		ppfk.fd[ppfk.i] = ftm_malloc((2) * sizeof(int));
		pipe(ppfk.fd[ppfk.i]);
		ppfk.i++;
	}
	ppfk.i = 0;
	ppfk.pid = pid;
	while (ppfk.i < nb_command)
	{
		pipe_choose(ppfk, pipe_cmd, nb_command, nbr_pipe);
		ppfk.i++;
	}
	pipe_wait(ppfk, nb_command, pid);
}
