/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:11:35 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 22:34:21 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_export_manual(t_env **env_lst)
{
	t_export	*export;

	export = add_export(4);
	export->name = ft_strdup_("OLDPWD");
	ft_export_exec(env_lst, export);
	ftm_free(export);
}
