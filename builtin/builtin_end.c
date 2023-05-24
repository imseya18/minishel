/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:01:42 by loculy            #+#    #+#             */
/*   Updated: 2023/05/22 14:05:03 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_end_a(char c)
{
	if (c != ' ' && c != '\t' && c != '\'' && c != '"' && c != '|')
		return (1);
	else
		return (0);
}

int	builtin_end_b(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}
