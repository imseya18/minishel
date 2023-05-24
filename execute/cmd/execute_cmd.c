/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:53:11 by mmorue            #+#    #+#             */
/*   Updated: 2023/05/24 13:19:33 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exc_cmd(t_minishell *main)
{
	t_command	*temp;
	t_command	**pipe_cmd;
	int			size;

	if (check_if_valid_command(main->cmd) == 0)
		return (free_command_all(main->cmd));
	temp = main->cmd;
	main->cmd = NULL;
	size = get_commands_size(temp);
	pipe_cmd = get_commands_arr(temp, size);
	get_signal_status(0);
	if (size > 0)
		ft_exec_pipe(size, pipe_cmd, get_nbr_of_pipe(&temp));
	else
		get_exit_code(0);
	get_signal_status(1);
	free_command_all(main->cmd);
}

void	ft_exit(t_exit *exit_code)
{
	long long	result;

	ft_printf("exit\n");
	if ((exit_code->code != NULL && ((ft_isdigit(exit_code->code[0]) == 0
					&& exit_code->code[0] != '-' && exit_code->code[0] != '+')
				|| (exit_code->code[1] && ft_isdigit(exit_code->code[1]) == 0)))
		|| exit_check_long(exit_code->code) == 1)
	{
		ft_printerror("minishell: exit: %s: numeric argument required\n",
			exit_code->code);
		exit(255);
	}
	if (exit_code->error == 1)
	{
		ft_printerror("minishell:%s\n", exit_code->error_msg);
		exit(1);
		return ;
	}
	if (exit_code->code)
		result = ft_atoi_long(exit_code->code);
	else
		result = 0;
	ftm_free_all();
	exit(result % 256);
}

char	*ft_exec_cdm_two(t_command *temp, t_minishell *main)
{
	if (temp->type == 2)
		return (ft_cd(temp->cmd, main));
	else if (temp->type == 4)
		return (ft_export_exec(&(main->var_env), temp->cmd));
	else if (temp->type == 5)
		return (ft_unset(&(main->var_env), temp->cmd));
	else if (temp->type == 7)
		ft_exit(temp->cmd);
	return (ft_strdup_(""));
}

char	*ft_exec_cdm_follow(t_command *temp, t_minishell *main)
{
	if (temp->type == 1)
		return (ft_print_echo(temp->cmd));
	else if (temp->type == 3)
		return (print_pwd(temp->cmd));
	else if (temp->type == 6)
		return (ft_printenv(main->var_env));
	return (ft_strdup_(""));
}

char	*ft_print_echo(t_echo *echo)
{
	char	*out;

	out = ft_strdup_(echo->value);
	if (echo->no_brkln == 0)
		out = ft_strjoin_char(out, '\n');
	get_exit_code(0);
	return (out);
}
