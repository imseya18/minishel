/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:19:39 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 13:54:51 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_valid_command(t_command *start)
{
	t_command	*temp;
	int			i;

	i = 0;
	temp = start;
	if (!temp)
		return (1);
	while (temp->next)
	{
		if ((temp->type == 100 && i == 0) || (temp->type == 100
				&& temp->next != 0 && temp->next->type == 100))
			break ;
		i++;
		temp = temp->next;
	}
	if (temp->type == 100)
	{
		ft_printerror("minishell: syntax error\n");
		get_exit_code(2);
		return (0);
	}
	return (1);
}

int	get_commands_size(t_command *start)
{
	int			size;
	t_command	*temp;
	int			pipe;

	pipe = 1;
	temp = start;
	size = 0;
	while (temp)
	{
		if ((temp->type == 1 || temp->type == 2 || temp->type == 3
				|| temp->type == 6 || temp->type == 4 || temp->type == 5
				|| temp->type == 7 || temp->type == 8) && pipe == 1)
		{
				size++;
			pipe = 0;
		}
		else if (temp->type == 100)
			pipe = 1;
		temp = temp->next;
	}
	return (size);
}

t_command	**get_commands_arr(t_command *start, int size)
{
	int			i;
	t_command	*temp;
	t_command	*act;
	t_command	**out;

	i = 0;
	out = ftm_malloc((size + 1) * sizeof(t_command *));
	temp = start;
	while (temp)
	{
		out[i] = 0;
		if (temp != 0 && temp->type != 202)
			out[i++] = temp;
		while (temp && temp->type != 100)
			temp = temp->next;
		if (temp)
		{
			act = temp->next;
			temp->next = 0;
			temp = act;
		}
	}
	out[i] = NULL;
	return (out);
}

char	*get_commands_type(t_command *start, int size)
{
	int			i;
	char		*out;
	t_command	*temp;

	temp = start;
	out = ftm_malloc((size + 1) * sizeof(char));
	i = 0;
	while (temp)
	{
		if (temp->type == 1 || temp->type == 2 || temp->type == 3
			|| temp->type == 6 || temp->type == 4 || temp->type == 5
			|| temp->type == 7)
		{
				out[i++] = '1';
		}
		else if (temp->type == 8)
			out[i++] = '0';
		temp = temp->next;
	}
	out[i++] = 0;
	return (out);
}
