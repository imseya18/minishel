/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seya <seya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:43:46 by loculy            #+#    #+#             */
/*   Updated: 2023/05/07 02:29:59 by seya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../../memory_manager/memory_manager.h"

static void	ft_free_all(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size && tab[i] != NULL)
		ftm_free(tab[i++]);
	ftm_free(tab);
}

static int	ft_check_nbr(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}	
	return (j);
}

static char	*ft_split_word(char const *s, char c, int *pose, int *error)
{
	int		sizei;
	int		j;
	char	*m;

	j = 0;
	sizei = 0;
	while (s[*pose] && s[*pose] == c)
		*pose = *pose + 1;
	while (s[*pose + sizei] && s[*pose + sizei] != c)
		sizei++;
	m = ftm_malloc((sizei + 1) * sizeof(char));
	if (!m)
	{
		*error = 1;
		return (0);
	}
	while (j < sizei)
	{
		m[j++] = s[*pose];
		*pose = *pose + 1;
	}
	m[j++] = '\0';
	return (m);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		pose;
	int		wordnb;
	char	**out;
	int		error;

	i = 0;
	pose = 0;
	error = 0;
	if (!s)
		return (0);
	wordnb = ft_check_nbr(s, c);
	out = ftm_malloc(sizeof(char *) * (wordnb + 1));
	if (!out)
		return (NULL);
	while (i < wordnb && error == 0)
			out[i++] = ft_split_word(s, c, &pose, &error);
	if (error == 1)
	{
		ft_free_all(out, wordnb + 1);
		return (0);
	}
	out[i] = 0;
	return (out);
}
