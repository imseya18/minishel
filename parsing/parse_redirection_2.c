/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:07:41 by loculy            #+#    #+#             */
/*   Updated: 2023/05/02 19:49:15 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redi_printable_2(int val_type, void *main_cmd)
{
	t_export	*export;
	t_unset		*unset;
	t_exit		*exit;

	if (val_type == 4)
	{
		export = (t_export *)main_cmd;
		export->printable = 0;
	}
	else if (val_type == 5)
	{
		unset = (t_unset *)main_cmd;
		unset->printable = 0;
	}
	else if (val_type == 7)
	{
		exit = (t_exit *)main_cmd;
		exit->printable = 0;
	}
}

void	redi_printable(int val_type, void *main_cmd)
{
	t_echo		*echo;
	t_cd		*cd;
	t_none		*none;

	if (val_type == 1)
	{
		echo = (t_echo *)main_cmd;
		echo->printable = 0;
	}
	else if (val_type == 2)
	{
		cd = (t_cd *)main_cmd;
		cd->printable = 0;
	}
	else if (val_type == 3 || val_type == 6)
	{
		none = (t_none *)main_cmd;
		none->printable = 0;
	}
	else
		redi_printable_2(val_type, main_cmd);
}

void	redi_err_2(int val_type, void *main_cmd, char *err)
{
	t_exit		*exit;

	if (val_type == 4)
		parse_export_error(main_cmd, 2, err);
	else if (val_type == 5)
		parse_unset_error(main_cmd, 2, err);
	else if (val_type == 7)
	{
		exit = (t_exit *)main_cmd;
		exit->error = 2;
		exit->error_msg = err;
	}
	else if (val_type == 8)
		parse_exec_error(main_cmd, 2, err);
}

void	redi_err(int val_type, void *main_cmd, char *err)
{
	if (val_type == 1)
		parse_echo_error(main_cmd, 2, err);
	else if (val_type == 2)
		parse_cd_error(main_cmd, 2, err);
	else if (val_type == 3 || val_type == 6)
		parse_none_error(main_cmd, 2, err);
	else
		redi_printable_2(val_type, main_cmd);
}

t_builtin	*get_redirection_err(int val_type,
	t_raw_builtin *raw, void *main_cmd, char c)
{
	int		size;
	char	*err;

	size = 1;
	if (raw != 0)
		raw = raw->next;
	if (raw != 0 && (raw->chara == '>' || raw->chara == '<'))
		size = 2;
	if (size == 1)
	{
		if (c == '>')
			err = ft_strdup_(" syntax error near unexpected token `>'");
		else
			err = ft_strdup_(" syntax error near unexpected token `<'");
	}
	else
	{
		if (c == '>')
			err = ft_strdup_(" syntax error near unexpected token `>>'");
		else
			err = ft_strdup_(" syntax error near unexpected token `<<'");
	}
	redi_err(val_type, main_cmd, err);
	return (0);
}
