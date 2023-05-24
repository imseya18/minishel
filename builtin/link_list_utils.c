/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:20:57 by loculy            #+#    #+#             */
/*   Updated: 2023/05/09 17:56:38 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_link_list_size(t_raw_builtin *raw)
{
	int				i;

	i = 0;
	while (raw != 0)
	{
		raw = raw->next;
		i++;
	}
	return (i);
}

char	*link_list_to_str(t_raw_builtin *raw, int size)
{
	t_raw_builtin	*tmp;
	char			*out;
	int				i;

	i = 0;
	out = ftm_malloc(sizeof(char) * (size + 1));
	while (raw != 0)
	{
		tmp = raw;
		out[i++] = raw->chara;
		raw = raw->next;
		ftm_free(tmp);
	}
	return (out);
}
