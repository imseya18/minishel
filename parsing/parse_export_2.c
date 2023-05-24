/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:47:45 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 17:25:27 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_export_error_quote(t_export *export, t_builtin *start)
{
	if (export->name != 0)
		ftm_free(export->name);
	if (export->content != 0)
		ftm_free(export->content);
	export->name = 0;
	export->content = 0;
	export->printable = 0;
	export->error = 1;
	clear_cmd_list(start);
}

void	parse_export_error(t_export *export, int error, char *error_msg)
{
	export->error = error;
	export->error_msg = error_msg;
}

void	parse_export_error_msg(t_export *export)
{
	export->error = 1;
	export->error_msg = ft_strjoin_(export->name, "': not a valid identifier");
}

void	parse_export_checkformat(t_export *export)
{
	int	i;

	i = 0;
	if (!export->name)
		return ;
	if (ft_isalpha(export->name[0]) != 1 && export->name[0] != '_')
		return (parse_export_error_msg(export));
	while (export->name[++i])
	{
		if (ft_isalnum(export->name[i]) != 1)
			return (parse_export_error_msg(export));
	}
}

int	parse_export_is_empty(t_export *export)
{
	if (export->envable == 0 && export->name == 0 && export->content == 0
		&& export->error == 0)
		return (1);
	return (0);
}
