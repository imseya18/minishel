/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:20:19 by loculy            #+#    #+#             */
/*   Updated: 2023/05/09 10:46:12 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clear_bf(char *buffer, char *a, char *b)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
		buffer[i++] = 0;
	ftm_free(a);
	ftm_free(b);
	return (0);
}

size_t	ft_strlengnl(char *s)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	char			*m;
	unsigned int	size;
	unsigned int	j;
	unsigned int	i;

	j = 0;
	if (!s1 && s2)
		return (s2);
	if (!s1 && !s2)
		return (0);
	size = ft_strlengnl(s1) + ft_strlengnl(s2);
	m = ftm_malloc(size * sizeof(char) + 1);
	if (!m)
		return (NULL);
	i = 0;
	while (s1[i])
		m[j++] = s1[i++];
	ftm_free(s1);
	i = 0;
	while (s2[i])
		m[j++] = s2[i++];
	m[size] = '\0';
	ftm_free(s2);
	return (m);
}
