/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:42:24 by loculy            #+#    #+#             */
/*   Updated: 2023/05/22 18:03:16 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//void	ft_create_file(char *file_name, int type)
//{
//	int	fd;
//
//	if (type == 12)
//		unlink(file_name);
//	fd = open(file_name, O_CREAT | O_RDWR, S_IRUSR
//			| S_IWUSR | S_IRGRP | S_IROTH);
//	close(fd);
//}
//
//void	ft_write_in_file(char *file_name, char *msg)
//{
//	int	fd;
//
//	fd = open(file_name, O_APPEND);
//	write(fd, msg, ft_strlen_(msg));
//	close(fd);
//}
//
//void	ft_redirection(t_echo *echo)
//{
//	(void)echo;
//}
//
//int	get_file_acces(char *path)
//{
//	int	fd;
//
//	fd = open(path, O_RDONLY);
//	if (access(path, F_OK) != 0)
//	{
//		//ft_printerror("%s: No such file or directory\n", path);
//		return (1);
//	}
//	if (access(path, R_OK) != 0)
//	{
//		//ft_printerror("%s: Permission denied\n", path);
//		return (2);
//	}
//	printf("=>=>=> %d\n", fd);
//	return (0);
//}
