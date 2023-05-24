/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:20:14 by mmorue            #+#    #+#             */
/*   Updated: 2023/05/23 23:00:56 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_dir_fill(int size, int i, char *path)
{
	int		k;
	char	*out;

	out = ftm_malloc(sizeof(char) * (size + 1));
	k = 0;
	while (k < size && path[i])
		out[k++] = path[i++];
	out[k++] = 0;
	return (out);
}

char	*get_dir(char *path)
{
	int		i;
	int		size;

	i = ft_strlen_(path) - 1;
	size = 0;
	while (i >= 0 && path[i] == '/')
		i--;
	while (i >= 0 && path[i] != '/')
	{
		i--;
		size++;
	}
	if (i == -1 && path[0] == '/')
	{
		size = 1;
		i = 0;
	}
	else
		i++;
	return (get_dir_fill(size, i, path));
}

void	ft_changepwd(t_env **env)
{
	t_env	*pwd;
	t_env	*old_pwd;

	pwd = *env;
	old_pwd = *env;
	while (pwd && ft_strcmp("PWD", pwd->name) != 0)
		pwd = pwd->next;
	while (old_pwd)
	{
		if (ft_strcmp("OLDPWD", old_pwd->name) == 0 && pwd->name)
		{
			ftm_free(old_pwd->content);
			old_pwd->content = ft_strdup(pwd->content);
			ftm_add_track(old_pwd->content);
			break ;
		}
		else if (ft_strcmp("OLDPWD", old_pwd->name) == 0 && pwd->name == NULL)
			old_pwd->content = ft_strdup(0);
		old_pwd = old_pwd->next;
	}
	if (pwd->name)
	{
		ftm_free(pwd->content);
		pwd->content = get_pwd();
	}
}

char	*ft_cd(t_cd *cd, t_minishell *main)
{
	char	*path;

	if (!cd->path)
		cd->path = ft_strjoin_("/Users/", env_get_user(&(main->var_env)));
	path = get_dir(cd->path);
	if (chdir(cd->path) != 0)
	{
		set_exit_code(1);
		ft_printerror("minishell: cd: %s\n", strerror (errno));
		ftm_free(path);
	}
	else
	{
		ftm_free(main->actual_dir);
		ft_changepwd(&main->var_env);
		path = get_dir(get_pwd());
		main->actual_dir = path;
		set_exit_code(0);
		ft_get_readln_disp(main);
	}
	return (ft_strdup_(""));
}
