/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seya <seya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:47:26 by loculy            #+#    #+#             */
/*   Updated: 2023/05/18 22:50:23 by seya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup_(char *str)
{
	int		i;
	char	*out;
	int		sizestr;

	i = 0;
	sizestr = ft_strlen_(str);
	out = ftm_malloc(sizeof(char) * (sizestr + 1));
	while (i < sizestr && str[i])
	{
		out[i] = str[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

char	*ft_strjoin_(char *s1, char *s2)
{
	char	*m;
	int		size;
	int		j;
	int		i;

	i = 0;
	if (!s1)
		return (s2);
	size = ft_strlen_(s1) + ft_strlen_(s2);
	m = ftm_malloc(size * sizeof(char) + 1);
	if (!m)
		return (NULL);
	j = 0;
	while (j < ft_strlen_(s1))
		m[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen_(s2))
		m[i++] = s2[j++];
	m[i] = '\0';
	return (m);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	char	*m;
	int		size;
	int		j;
	int		i;

	i = 0;
	size = ft_strlen_(s1) + 1;
	m = ftm_malloc(size * sizeof(char) + 1);
	if (!m)
		return (0);
	j = 0;
	while (j < ft_strlen_(s1))
		m[i++] = s1[j++];
	m[i++] = s2;
	m[i] = '\0';
	if (s1 != 0)
		ftm_free(s1);
	return (m);
}

char	*remove_end_char(char *str, int last)
{
	char	*out;
	int		i;
	int		size;

	i = 0;
	size = ft_strlen_(str) - last;
	if (size < 0)
		size = 0;
	out = ftm_malloc(sizeof(char) * (size + 1));
	while (i < size && str[i])
	{
		out[i] = str[i];
		i++;
	}
	out[i] = 0;
	if (str != 0)
		ftm_free(str);
	return (out);
}
