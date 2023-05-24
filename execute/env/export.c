/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:40 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 23:01:43 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_export_new(t_export *export)
{
	t_env			*env_link;

	env_link = ftm_malloc(sizeof(t_env));
	if (!env_link)
		return (0);
	env_link->name = export->name;
	env_link->content = export->content;
	env_link->next = NULL;
	return (env_link);
}

void	ft_export_add_back(t_env **lst, t_env *new)
{
	t_env	*act;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	act = *lst;
	while (act->next != NULL)
		act = act->next;
	act->next = new;
}

char	*ft_export_set_content(char *content, t_export *exp, int type)
{
	char	*out;

	if (exp->egal == 2)
		out = ft_strjoin_frees1(content, exp->content);
	else
	{
		if (exp->egal == 1)
		{
			out = exp->content;
			if (!exp->content)
				out = ft_strdup_("");
		}
		else
		{
			if (type == 1)
				out = ft_strdup_(content);
			else
				out = 0;
		}
		ftm_free(content);
	}
	return (out);
}

int	ft_check_if_exist(t_env **env_lst, t_export *exp)
{
	t_env	*temp;
	t_env	*new;

	temp = *env_lst;
	while (temp)
	{
		if (ft_strcmp(temp->name, exp->name) == 0)
		{
			temp->content = ft_export_set_content(temp->content, exp, 1);
			return (1);
		}
		temp = temp->next;
	}
	new = ft_export_new(exp);
	new->content = ft_export_set_content(0, exp, 0);
	ft_export_add_back(env_lst, new);
	return (0);
}

char	*ft_export_exec(t_env **env_lst, t_export *export)
{
	if (export->error_msg != 0)
	{
		ft_printerror("minishell: export: %s\n", export->error_msg);
		set_exit_code(1);
		return (ft_strdup_(""));
	}
	if (export->name == NULL && export->envable != 1)
	{
		if (export->egal == 1 || export->egal == 0)
			ft_printerror("minishell: export: `=': not a valid identifier\n");
		else
			ft_printerror("minishell: export: `+=': not a valid identifier\n");
		set_exit_code(1);
		return (ft_strdup_(""));
	}
	else if (export->envable == 1)
		return (ft_printenv_export(env_lst));
	else if (export->name != NULL && export->name[0] != 0)
		ft_check_if_exist(env_lst, export);
	set_exit_code(0);
	return (ft_strdup_(""));
}
