/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:38:19 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 22:52:21 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_var_size(t_raw_builtin *raw)
{
	t_raw_builtin	*tmp;
	int				size;
	int				exitcode;

	tmp = raw;
	size = 0;
	exitcode = 0;
	while (tmp != 0 && (ft_isalnum(tmp->chara) == 1 || tmp->chara == '_'
			|| (size == 0 && tmp->chara == '?')))
	{
		if (exitcode == 1)
			return (size);
		else if (tmp->chara == '?')
			exitcode = 1;
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	*get_var_key(t_raw_builtin *raw, int size)
{
	t_raw_builtin	*tmp;
	char			*key;
	int				i;

	tmp = raw;
	i = 0;
	key = ftm_malloc(sizeof(char) * (size + 1));
	while (tmp != 0 && (ft_isalnum(tmp->chara) == 1 || tmp->chara == '_'
			|| (i == 0 && tmp->chara == '?')))
	{
		if (i > 0 && key[i - 1] == '?')
			break ;
		key[i++] = tmp->chara;
		tmp = tmp->next;
	}
	key[i++] = 0;
	return (key);
}
