/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:32:27 by loculy            #+#    #+#             */
/*   Updated: 2023/05/16 16:03:46 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_command_a(t_command *cmd)
{
	if (cmd->type == 1)
	{
		ftm_free(((t_echo *)cmd->cmd)->value);
		ftm_free(((t_echo *)cmd->cmd)->error_msg);
	}
	else if (cmd->type == 2)
	{
		ftm_free(((t_cd *)cmd->cmd)->path);
		ftm_free(((t_cd *)cmd->cmd)->error_msg);
	}
	else if (cmd->type == 3 || cmd->type == 6 || cmd->type == 202)
		ftm_free(((t_none *)cmd->cmd)->error_msg);
	else if (cmd->type == 4)
	{
		ftm_free(((t_export *)cmd->cmd)->name);
		ftm_free(((t_export *)cmd->cmd)->content);
		ftm_free(((t_export *)cmd->cmd)->error_msg);
	}
	else if (cmd->type == 5)
	{
		ftm_free(((t_unset *)cmd->cmd)->name);
		ftm_free(((t_unset *)cmd->cmd)->error_msg);
	}
}

void	free_command_b(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->type == 7)
	{
		ftm_free(((t_exit *)cmd->cmd)->code);
		ftm_free(((t_exit *)cmd->cmd)->error_msg);
	}
	else if (cmd->type == 8)
	{
		ftm_free(((t_exec *)cmd->cmd)->cmd_path);
		while (((t_exec *)cmd->cmd)->data != 0
			&& ((t_exec *)cmd->cmd)->data[i] != 0)
			ftm_free(((t_exec *)cmd->cmd)->data[i++]);
		ftm_free(((t_exec *)cmd->cmd)->error_msg);
	}
	if (cmd->type == 101 || cmd->type == 102 || cmd->type == 103
		|| cmd->type == 104)
	{
		ftm_free(((t_redirection *)cmd->cmd)->file_name);
		ftm_free(((t_redirection *)cmd->cmd)->error_msg);
	}
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == 1 || cmd->type == 2 || cmd->type == 3 || cmd->type == 6
		|| cmd->type == 4 || cmd->type == 5 || cmd->type == 202)
		free_command_a(cmd);
	else if (cmd->type == 101 || cmd->type == 102 || cmd->type == 103
		|| cmd->type == 104 || cmd->type == 7 || cmd->type == 8)
		free_command_b(cmd);
	ftm_free(cmd->cmd);
	ftm_free(cmd);
}

void	free_command_all(t_command *start)
{
	t_command	*temp;
	t_command	*back;

	temp = start;
	back = NULL;
	while (temp)
	{
		back = temp;
		temp = temp->next;
		free_command(back);
	}
}
