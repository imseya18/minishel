/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:37:49 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 13:53:55 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_file_acces(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (access(path, F_OK) != 0)
		return (1);
	if (access(path, R_OK) != 0)
		return (2);
	return (0);
}

int	get_file_acces_exec(char *path)
{
	int	return_code;

	return_code = get_file_acces(path);
	if (return_code == 0)
		return (0);
	if (return_code == 1)
		return (1);
	else if (return_code == 2)
		error_msg_exit("minishell: Permission denied");
	return (0);
}

void	write_append_file(char *path, char *file_act, char *file_append)
{
	int		fd;
	char	*out;

	out = ft_strjoin_(file_act, file_append);
	ftm_free(file_act);
	ftm_free(file_append);
	fd = open(path, O_WRONLY);
	write(fd, out, ft_strlen_(out));
	ftm_free(out);
	close(fd);
}

void	create_file(char *path, int type)
{
	int	fd;

	if (type == 101)
		unlink(path);
	fd = open(path, O_CREAT | O_RDWR, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
	close(fd);
}
