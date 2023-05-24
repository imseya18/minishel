/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_redirection_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:37:36 by loculy            #+#    #+#             */
/*   Updated: 2023/05/09 16:47:52 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtin_line(char *str, t_builtin **head_bltn, int i)
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
			i++;
		}
		else
			i++;
	}
}

char	*get_quote(char *out, int type)
{
	if (type == 3)
		out = ft_strjoin_char(out, '\'');
	else if (type == 2)
		out = ft_strjoin_char(out, '"');
	return (out);
}

void	set_stdin(void *main_cmd, t_redirection *redi, int type)
{
	t_exec	*exec;

	if (type == 8)
	{
		exec = (t_exec *)main_cmd;
		exec->stdin = redi;
	}
}
