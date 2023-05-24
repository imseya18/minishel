/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_result.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:26:46 by loculy            #+#    #+#             */
/*   Updated: 2023/04/12 16:32:04 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lstclean(t_plist **lst)
{
	t_plist	*ll;
	t_plist	*tmp;

	if (lst == NULL)
		return ;
	ll = *lst;
	tmp = *lst;
	while (ll != NULL)
	{
		tmp = ll->next;
		if (ll->content != NULL)
			free(ll->content);
		free(ll);
		ll = tmp;
	}
	*lst = NULL;
}

void	ft_res_read(t_plist *act, char *res)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	if (!act)
		return ;
	while (act->next != NULL)
	{
		j = 0;
		s = act->content;
		while (j < act->size)
			res[i++] = s[j++];
		act = act->next;
	}
	j = 0;
	s = act->content;
	while (j < act->size)
		res[i++] = s[j++];
	res[i] = '\0';
}

int	ft_result(int size, t_plist *out, int *error)
{
	char	*m;
	size_t	ch;

	if (*error == 1)
		return (-1);
	m = malloc(size + 1 * sizeof(char));
	if (!m)
		return (-1);
	ft_res_read(out, m);
	ch = write(1, m, size);
	free(m);
	if (ch == (size_t)-1)
		return (-1);
	return (size);
}

int	ft_result_err(int size, t_plist *out, int *error)
{
	char	*m;
	size_t	ch;

	if (*error == 1)
		return (-1);
	m = malloc(size + 1 * sizeof(char));
	if (!m)
		return (-1);
	ft_res_read(out, m);
	ch = write(2, m, size);
	free(m);
	if (ch == (size_t)-1)
		return (-1);
	return (size);
}
