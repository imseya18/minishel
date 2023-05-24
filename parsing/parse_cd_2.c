/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:53:03 by loculy            #+#    #+#             */
/*   Updated: 2023/05/01 15:25:09 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_cd_error_quote(t_cd *cd, t_builtin *start)
{
	if (cd->path != 0)
		ftm_free(cd->path);
	cd->path = 0;
	cd->printable = 0;
	clear_cmd_list(start);
}

void	parse_cd_error(t_cd *cd, int error, char *error_msg)
{
	cd->error = error;
	cd->error_msg = error_msg;
}
