/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:19:19 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 22:59:35 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_minishell	*get_main(void *input)
{
	static t_minishell	*main;

	if (input != 0)
	{
		main = (t_minishell *)input;
	}
	return (main);
}

int	get_exit_code(int input)
{
	static int	code;

	if (input != 1000)
	{
		code = input;
	}
	return (code);
}

int	get_signal_status(int input)
{
	static int	code;

	if (input != 2)
	{
		code = input;
	}
	return (code);
}

void	set_exit_code(int input)
{
	if (get_exit_code(1000) < input)
		get_exit_code(input);
}
