/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:05:28 by mmorue            #+#    #+#             */
/*   Updated: 2023/05/17 17:07:01 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_dir_exec(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	exec_path(t_minishell *main, t_exec *exec, char *path)
{
	char	**env_tab;
	pid_t	pid;
	int		status;

	(void)exec;
	env_tab = NULL;
	env_tab = env_fork(main->var_env);
	pid = fork();
	if (pid == 0)
		execve(path, exec->data, env_tab);
	else if (pid > 0)
	{
		wait(&status);
		get_exit_code(WEXITSTATUS(status));
	}
	ftm_free(env_tab);
}
