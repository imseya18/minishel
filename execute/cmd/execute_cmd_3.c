/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:51:09 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 16:10:07 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_check_max(char *input, char *long_max)
{
	int	i;

	i = 0;
	while (long_max[i])
	{
		if (long_max[i] != input[i])
			return (input[i] - long_max[i]);
		i++;
	}
	return (input[i] - long_max[i]);
}

int	exit_check_size(char *input)
{
	int	size;

	size = ft_strlen_(input);
	if (size == 19)
		return (1);
	else if (size > 19)
		return (2);
	else
		return (0);
}

int	exit_check_if_negative(char *input)
{
	if (ft_strlen_(input) > 0)
		if (input[0] == '-')
			return (1);
	return (0);
}

int	exit_compare(char *input, char *compare)
{
	if (exit_check_size(input) == 1)
	{
		if (exit_check_max(input, compare) > 0)
			return (1);
	}
	else if (exit_check_size(input) == 2)
		return (1);
	return (0);
}

int	exit_check_long(char *input)
{
	if (!input)
		return (0);
	if (exit_check_if_negative(input) == 1)
		return (exit_compare(++input, "9223372036854775808"));
	else
		return (exit_compare(input, "9223372036854775807"));
	return (0);
}
