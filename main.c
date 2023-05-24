/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:11:15 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 15:29:56 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_readln_disp(t_minishell	*main)
{
	char	*a;
	char	*b;

	ftm_free(main->console);
	a = ft_strjoin_(env_get_user(&main->var_env), "@minishell ");
	b = ft_strjoin_(a, main->actual_dir);
	ftm_free(a);
	main->console = ft_strjoin_(b, " ➤ ");
	ftm_free(b);
}

void	inthandler(int sig)
{
	if (sig == 2)
	{
		if (get_signal_status(2) == 0)
			return ;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 3)
		return ;
}

void	init_shell(t_minishell	*main, int argc, char **argv)
{
	env_init(argc + 1, argv, main);
	main->console = 0;
	main->actual_dir = get_dir(get_pwd());
	ft_get_readln_disp(main);
	rl_catch_signals = 0;
	get_signal_status(1);
	add_export_manual(&(main->var_env));
	signal(SIGINT, inthandler);
	signal(SIGQUIT, inthandler);
}

int	main(int argc, char **argv)
{
	t_minishell	main;

	main.var_env = NULL;
	init_shell(&main, argc, argv);
	main.command = readline(main.console);
	while (main.command != 0)
	{
		main.cmd = 0;
		main.cmd_exit_code = 0;
		get_parsed_command(main.command, &main);
		ft_exc_cmd(&main);
		rl_on_new_line();
		main.command = readline(main.console);
	}
	ft_printf("\033[A\033[2K%sexit\n", main.console);
	ftm_free_all();
	return (0);
}
