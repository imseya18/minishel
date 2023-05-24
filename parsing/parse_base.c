/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:36:46 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 17:26:14 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_base(t_builtin **head_bltn, t_minishell *main)
{
	parse_var(head_bltn, main);
	parse_backslash(head_bltn);
}

void	parsing_ending(t_command **lst, t_minishell *main)
{
	t_command	*act;

	if (!*lst)
		return ;
	act = *lst;
	(void)main;
	while (act != NULL)
	{
		if (act->type == 4)
			parse_export_checkformat(act->cmd);
		else if (act->type == 5)
			parse_unset_checkformat(act->cmd);
		act = act->next;
	}
}

void	get_parsed_command(char *str, t_minishell *main)
{
	t_builtin		*head_bltn;
	t_parsed_cmd	*cmd;
	t_command		*all_cmd;

	head_bltn = 0;
	cmd = 0;
	all_cmd = 0;
	add_history(str);
	get_main(main);
	ft_builtin(str, &head_bltn, 0);
	parse_base(&head_bltn, main);
	parse_cmd(&head_bltn, &cmd);
	get_cmds(&cmd, &all_cmd, main);
	parsing_ending(&all_cmd, main);
	main->cmd = all_cmd;
}
