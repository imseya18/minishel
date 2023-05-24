/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:55 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 18:55:26 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_frees1(char *s1, char *s2)
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
	ftm_free(s1);
	return (m);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (s1 && !s2)
		return (1);
	else if (!s1 && s2)
		return (-1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup_buff(char *str)
{
	unsigned int		i;
	char				*out;
	unsigned int		sizestr;

	i = 0;
	sizestr = ft_strlen(str);
	out = ftm_malloc(sizeof(char) * (sizestr + 1));
	printf("**B\n");
	while (i < sizestr && str[i] && i < 1024)
	{
		out[i] = str[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

char	*ft_strjoin_frees1_buff(char *s1, char *s2)
{
	char			*m;
	unsigned int	size;
	unsigned int	j;
	unsigned int	i;

	i = 0;
	if (!s1)
		return (s2);
	size = ft_strlen(s1) + ft_strlen(s2);
	m = ftm_malloc(size * sizeof(char) + 1);
	if (!m)
		return (NULL);
	j = 0;
	while (j < ft_strlen(s1))
		m[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
		m[i++] = s2[j++];
	m[i] = '\0';
	ftm_free(s1);
	return (m);
}
