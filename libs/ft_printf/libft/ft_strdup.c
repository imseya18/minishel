/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:13:38 by loculy            #+#    #+#             */
/*   Updated: 2023/04/18 18:00:30 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlenloc(const char *s1)
{
	int	i;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*m;
	int		i;
	int		sizes1;

	i = 0;
	sizes1 = ft_strlenloc(s1);
	m = (char *)malloc((sizes1 + 1) * sizeof(char));
	if (!m)
		return (0);
	while (i < sizes1)
	{
		m[i] = s1[i];
		i++;
	}
	m[i] = '\0';
	return (m);
}
