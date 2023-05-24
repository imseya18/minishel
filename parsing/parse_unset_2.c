/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unset_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:18:53 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 17:25:36 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_unset_error_quote(t_unset *unset, t_builtin *start)
{
	if (unset->name != 0)
		ftm_free(unset->name);
	unset->name = 0;
	unset->printable = 0;
	clear_cmd_list(start);
}

void	parse_unset_error(t_unset *unset, int error, char *error_msg)
{
	unset->error = error;
	unset->error_msg = error_msg;
}

void	parse_unset_error_msg(t_unset *unset)
{
	unset->error = 1;
	unset->error_msg = ft_strjoin_(unset->name, "': not a valid identifier");
}

void	parse_unset_checkformat(t_unset *unset)
{
	int	i;

	i = 0;
	if (!unset->name)
		return ;
	if (ft_isalpha(unset->name[0]) != 1 && unset->name[0] != '_')
		return (parse_unset_error_msg(unset));
	while (unset->name[++i])
	{
		if (ft_isalnum(unset->name[i]) != 1)
			return (parse_unset_error_msg(unset));
	}
}
