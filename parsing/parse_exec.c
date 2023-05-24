/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:04:12 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 15:45:21 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*add_exec(int type)
{
	t_exec			*cmdexec;

	cmdexec = ftm_malloc(sizeof(t_exec));
	if (!cmdexec)
		return (0);
	cmdexec->type = type;
	cmdexec->cmd_path = NULL;
	cmdexec->data = NULL;
	cmdexec->printable = 0;
	cmdexec->error = 0;
	cmdexec->error_msg = NULL;
	cmdexec->stdin = NULL;
	return (cmdexec);
}

void	exec_add_flags(t_exec *exec, char *flag)
{
	int		i;
	int		size;
	char	**new;

	i = 0;
	size = 0;
	if (!exec)
		return ;
	while (exec->data != 0 && exec->data[size] != 0)
		size++;
	new = ftm_malloc(sizeof(char *) * (size + 2));
	while (exec->data != 0 && exec->data[i] != 0)
	{
		new[i] = exec->data[i];
		i++;
	}
	new[i++] = flag;
	new[i++] = 0;
	ftm_free(exec->data);
	exec->data = new;
}

void	parse_exec(t_builtin *start, t_command **all_cmd)
{
	t_builtin		*tmp;
	t_exec			*exec;
	int				pose;

	pose = 0;
	exec = add_exec(8);
	ft_cmd_add_back(all_cmd, ft_cmdnew(exec, 8));
	tmp = parse_skip_space(start);
	if (tmp->type == -1)
		return (clear_cmd_list(start));
	if (tmp->type == 0)
		pose = 1;
	if (pose == 0)
		tmp = get_exec_path(tmp, exec, &pose);
	start = get_redirection_auto(tmp, 8, exec, all_cmd);
	tmp = parse_skip_space(start);
	if (pose == 1)
		tmp = get_exec_flags(tmp, exec, &pose, all_cmd);
	if (pose == 2)
		tmp = get_exec_argum(tmp, exec, all_cmd);
	if (tmp != 0 && tmp->type == -1)
		return (parse_exec_error_quote(exec, start));
	clear_cmd_list(start);
}
