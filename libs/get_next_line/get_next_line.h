/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:10:45 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 19:02:48 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../memory_manager/memory_manager.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char		*ft_readjoin(char *buffer, char *line);
char		*ft_clear_bf(char *buffer, char *a, char *b);
size_t		ft_strlengnl(char *s);
char		*ft_strjoingnl(char *s1, char *s2);
void		ft_buffer_mg(char *buffer);
char		*ft_read(char *buffer);
char		*ft_read_line(int fd, char *buffer, char *line, ssize_t sz_file);
char		*get_next_line(int fd);

#endif