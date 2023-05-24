/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:19:44 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 22:52:29 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_raw_builtin	*unlink_var_key(t_raw_builtin *raw, int size)
{
	t_raw_builtin	*tmp;
	t_raw_builtin	*del;
	int				i;

	tmp = raw->next;
	ftm_free(raw);
	i = 0;
	while (tmp != 0 && (ft_isalnum(tmp->chara) == 1
			|| tmp->chara == '_' || (i == 0 && tmp->chara == '?'))
		&& i < size)
	{
		i++;
		del = tmp;
		tmp = tmp->next;
		ftm_free(del);
	}
	return (tmp);
}

t_raw_builtin	*get_parse_env(t_raw_builtin *act, int size, t_minishell *main)
{
	t_raw_builtin	*last;
	t_raw_builtin	*new;
	t_raw_builtin	*tmp;
	char			*str;
	int				i;

	if (size == 0)
		return (act);
	i = 0;
	new = 0;
	str = ft_get_env(&main->var_env, get_var_key(act->next, size));
	last = unlink_var_key(act, size);
	if (str != 0 && str[0] == 0)
	{
		tmp = ft_rawnnew('\0');
		ft_rawadd_back(&new, tmp);
	}
	while (str != 0 && i < ft_strlen_(str) && str[i] != 0)
	{
		tmp = ft_rawnnew(str[i]);
		ft_rawadd_back(&new, tmp);
		i++;
	}
	tmp->next = last;
	return (new);
}

void	get_parse_var(t_builtin *act_bltn, t_raw_builtin *raw, t_minishell *mn)
{
	t_raw_builtin	*tmp;
	t_raw_builtin	*back;

	tmp = raw;
	back = 0;
	while (tmp != 0)
	{
		if (tmp->chara == '$')
		{
			if (back == 0)
			{
				act_bltn->raw = get_parse_env(tmp, get_var_size(tmp->next), mn);
				tmp = act_bltn->raw;
			}
			else
			{
				back->next = get_parse_env(tmp, get_var_size(tmp->next), mn);
				tmp = back->next;
			}
		}
		back = tmp;
		if (tmp != 0)
			tmp = tmp->next;
	}
}

void	parse_var(t_builtin **head_bltn, t_minishell *main)
{
	t_builtin	*act_bltn;

	act_bltn = *head_bltn;
	while (act_bltn != 0)
	{
		if (act_bltn->type != 3)
			get_parse_var(act_bltn, act_bltn->raw, main);
		act_bltn = act_bltn->next;
	}
}
