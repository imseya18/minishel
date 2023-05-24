/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:08:52 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 13:04:21 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin_quote(char *str, int i, char c, t_builtin **head_bltn)
{
	t_raw_builtin	*act_raw;

	act_raw = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (c == '"')
				ft_bltnadd_back(head_bltn, ft_bltnnew(act_raw, 2));
			else
				ft_bltnadd_back(head_bltn, ft_bltnnew(act_raw, 3));
			return (++i);
		}
		else
			ft_rawadd_back(&act_raw, ft_rawnnew(str[i]));
		i++;
	}
	ft_bltnadd_back(head_bltn, ft_bltnnew(act_raw, -1));
	return (i);
}

int	ft_builin_end(char *str, int i, char c, t_builtin **head_bltn)
{
	t_raw_builtin	*act_raw;

	act_raw = 0;
	(void)c;
	ft_rawadd_back(&act_raw, ft_rawnnew(str[i]));
	ft_bltnadd_back(head_bltn, ft_bltnnew(act_raw, 10));
	return (++i);
}

void	ft_builtin(char *str, t_builtin **head_bltn, int i)
{
	t_raw_builtin	*act_raw;

	while (str != 0 && i < ft_strlen_(str) && str[i] != 0)
	{
		act_raw = 0;
		while (str[i] && builtin_end_a(str[i]))
			ft_rawadd_back(&act_raw, ft_rawnnew(str[i++]));
		if (act_raw != 0)
			ft_bltnadd_back(head_bltn, ft_bltnnew(act_raw, 1));
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
			i = ft_builtin_quote(str, i + 1, str[i], head_bltn);
		else if (str[i] && builtin_end_b(str[i]))
			i = ft_builin_end(str, i, str[i], head_bltn);
		else if (str[i] && (str[i] == ' ' || str[i] == ' '))
		{
			if (i > 0 && str[i - 1] == '\\')
				ft_bltnadd_back(head_bltn, ft_bltnnew(ft_rawnnew(' '), 1));
			else
				ft_bltnadd_back(head_bltn, ft_bltnnew(ft_rawnnew(' '), 0));
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
		}
		else
			i++;
	}
}
