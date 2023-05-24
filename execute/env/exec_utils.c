/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:44:33 by mmorue            #+#    #+#             */
/*   Updated: 2023/05/24 13:59:41 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**env_fork(t_env *env)
{
	int		i;
	char	**env_tab;
	t_env	*start;

	start = env;
	i = ft_lstsize_env(env);
	env_tab = ftm_malloc((i + 1) * sizeof(char *));
	env_tab[i] = NULL;
	i = 0;
	while (start)
	{
		env_tab[i] = ft_strjoin(start->name, "=");
		env_tab[i] = ft_strjoin_frees1(env_tab[i], start->content);
		start = start->next;
		i++;
	}
	return (env_tab);
}

char	*check_path(t_env *env, char *exec)
{
	t_env	*start;
	char	**path;
	char	*exec_path;
	int		i;

	i = -1;
	start = env;
	path = NULL;
	while (start && ft_strcmp(start->name, "PATH") != 0)
		start = start->next;
	if (start != 0)
	{
		path = ft_split(start->content, ':');
		while (path[++i])
		{
			exec_path = ft_strjoin_(path[i], "/");
			exec_path = ft_strjoin_frees1(exec_path, exec);
			if (access(exec_path, F_OK | X_OK) == 0)
				return (exec_path);
			ftm_free(exec_path);
		}
	}
	return (NULL);
}

void	exec_local_check_cmd(char **a)
{
	if (a[0] != 0 && (a[0][0] == '>' || a[0][0] == '<'))
	{
		ft_printerror("minishell: syntax error near unexpected token `%s'\n",
			a[0]);
		exit(2);
	}
	else
	{
		ft_printerror("minishell: %s: command not found\n", a[0]);
		exit(127);
	}
}

void	exec_local(t_minishell *main, t_exec *exec, char **a)
{
	int		i;

	(void)exec;
	i = check_dir_exec(a[0]);
	if (i != 1)
		exec_local_check_cmd(a);
	if (access(a[0], F_OK) != 0)
	{
		ft_printerror("minishell: %s: %s\n", a[0], strerror (errno));
		exit(127);
	}
	if (is_dir(a[0]) == 0)
	{
		ft_printerror("minishell: is a directory\n");
		exit(126);
	}
	if (access(a[0], X_OK) != 0)
	{
		ft_printerror("minishell: %s: %s\n", a[0], strerror (errno));
		exit(126);
	}
	execve(a[0], a, env_fork(main->var_env));
}

void	check_to_exec(t_minishell *main, t_exec *exec)
{
	char	*path;

	path = check_path(main->var_env, exec->cmd_path);
	if (path != NULL)
		exec_path(main, exec, path);
	ftm_free(path);
}
