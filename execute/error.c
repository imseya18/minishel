/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:45:00 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 19:56:18 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg_exit(char *msg)
{
	ft_printerror("%s\n", msg);
	ftm_free_all();
	exit(1);
}

void	error_msg_exit_code(char *msg, int code)
{
	ft_printerror("%s\n", msg);
	ftm_free_all();
	exit(code);
}
