/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_long.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:50 by loculy            #+#    #+#             */
/*   Updated: 2023/05/16 14:46:02 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_calc_atoi(const char *str, int i, int neg)
{
	long long	res;

	res = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (neg == 1)
		res = -res;
	return (res);
}

long long	ft_checkstart_atoi(const char *str, int i)
{
	int		neg;
	char	c;

	neg = 0;
	c = str[i];
	while (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
	{
		i++;
		c = str[i];
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = 1;
		i++;
	}
	return (ft_calc_atoi(str, i, neg));
}

long long	ft_atoi_long(const char *str)
{
	if (ft_strlen(str) == 0)
		return (0);
	else
		return (ft_checkstart_atoi(str, 0));
}
