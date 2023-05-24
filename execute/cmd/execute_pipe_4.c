/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:45:05 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 11:55:30 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_bltn_check_redi(t_command *pipe_cmd)
{
	t_minishell	*main;
	t_command	*tmp;

	main = get_main(0);
	if (!pipe_cmd)
		return ;
	tmp = pipe_cmd;
	while (tmp != NULL)
	{
		if (tmp->type == 103)
			if (get_file_acces(((t_redirection *)tmp->cmd)->file_name) == 1)
				error_msg_exit("minishell: No such file or directory");
		if (tmp->type == 101 || tmp->type == 102 || tmp->type == 103)
			if (get_file_acces(((t_redirection *)tmp->cmd)->file_name) == 2)
				error_msg_exit("minishell: Permission denied");
		if (tmp->type == 101 || tmp->type == 102)
			create_file(((t_redirection *)tmp->cmd)->file_name, 102);
		tmp = tmp->next;
	}
}

char	*pipe_exec_bltn(t_command *pipe_cmd)
{
	t_minishell	*main;
	t_command	*tmp;
	char		*out;

	pipe_bltn_check_redi(pipe_cmd);
	main = get_main(0);
	if (!pipe_cmd)
		return (0);
	tmp = pipe_cmd;
	get_exit_code(0);
	while (tmp != NULL)
	{
		if (ft_check_type(tmp->type) == 1)
			out = ft_check_type_to_exec(tmp->type, tmp, main);
		tmp = tmp->next;
	}
	return (out);
}
