/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:40:02 by mmorue            #+#    #+#             */
/*   Updated: 2023/05/19 14:31:49 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_pwd(void)
{
	char	buff[1025];
	char	*str;
	int		size;

	size = 0;
	getcwd(buff, 1024);
	while (buff[size])
		size++;
	str = ftm_malloc((size + 1) * sizeof(char));
	str[size] = 0;
	size = -1;
	while (buff[++size])
		str[size] = buff[size];
	get_exit_code(0);
	return (str);
}

char	*print_pwd(t_pwd *pwd)
{
	char	*str;

	(void)pwd;
	str = get_pwd();
	str = ft_strjoin_frees1(str, "\n");
	return (str);
}
