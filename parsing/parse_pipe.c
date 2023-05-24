/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:18:33 by loculy            #+#    #+#             */
/*   Updated: 2023/05/11 14:54:57 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipe	*add_pipe(void)
{
	t_pipe			*cmdpipe;

	cmdpipe = ftm_malloc(sizeof(t_pipe));
	if (!cmdpipe)
		return (0);
	cmdpipe->type = 100;
	return (cmdpipe);
}

void	redhandler(int sig)
{
	if (sig == 2)
	{
		ft_printf("\033[A\033[2K\n");
		ftm_free_all();
		exit(0);
	}
}

void	redirection_by_sep(char *separator, int *fd)
{
	char	*line;
	char	*tmp_del;
	char	*out;

	out = ft_strdup("");
	line = parse_line(readline("> "));
	while (line != 0)
	{
		if (ft_strcmp(separator, line) != 0)
		{
			tmp_del = line;
			line = ft_strjoin_(tmp_del, "\n");
			ftm_free(tmp_del);
			tmp_del = out;
			out = ft_strjoin_(tmp_del, line);
			ftm_free(tmp_del);
		}
		else
			break ;
		rl_on_new_line();
		line = parse_line(readline("> "));
	}
	write(fd[1], out, ft_strlen_(out));
	ftm_free_all();
	exit(0);
}

char	*red_by_sep(char *separator, int *fd, pid_t pid)
{
	char	buffer[1];
	char	*out;
	int		status;

	if (pid == 0)
	{
		close(fd[0]);
		rl_catch_signals = 1;
		signal(SIGINT, redhandler);
		redirection_by_sep(separator, fd);
		return (0);
	}
	else
	{
		out = 0;
		waitpid(pid, &status, 0);
		close(fd[1]);
		while (read(fd[0], buffer, 1) == 1)
			out = ft_strjoin_char(out, buffer[0]);
		return (out);
	}
	return (0);
}
