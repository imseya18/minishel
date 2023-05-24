/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:10:01 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 13:09:03 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	into_file_exec(t_redirection *redi)
{
	int	fd;

	fd = ftm_open(redi->file_name, O_APPEND | O_WRONLY);
	return (fd);
}

void	buffer_to_null(char *bff, int size)
{
	int	i;

	i = 0;
	while (i < size)
		bff[i++] = 0;
}

void	set_file_stdin(char *path)
{
	int	fd;

	if (get_file_acces(path) == 1)
		error_msg_exit("minishell: No such file or directory");
	else if (get_file_acces(path) == 2)
		error_msg_exit("minishell: Permission denied");
	fd = ftm_open(path, O_RDONLY);
	dup2(fd, STDIN_FILENO);
}

int	is_dir(char *path)
{
	struct stat	res;

	stat(path, &res);
	return (S_ISREG(res.st_mode));
}
