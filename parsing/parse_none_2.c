/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_none_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:20:27 by loculy            #+#    #+#             */
/*   Updated: 2023/05/01 15:25:46 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_none_error_quote(t_none *none, t_builtin *start)
{
	none->printable = 0;
	none->error = 1;
	clear_cmd_list(start);
}

void	parse_none_error(t_none *none, int error, char *error_msg)
{
	none->error = error;
	none->error_msg = error_msg;
}
