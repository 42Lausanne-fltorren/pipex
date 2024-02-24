/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:29:50 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/24 11:08:13 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_thread(int fd_in, int fd_out, char **cmd)
{
	if (fd_in == -1 || fd_out == -1)
		_exit(1);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	execve(cmd[0], cmd, NULL);
	perror("Error: execve failed\n");
}

static void	ft_thread_in(t_pipex p, int i)
{
	close(p.pipe_fd[0]);
	ft_thread(p.fd_file_in, p.pipe_fd[1], p.cmds[i]);
}

static void	ft_thread_out(t_pipex p, int i)
{
	close(p.pipe_fd[1]);
	ft_thread(p.pipe_fd[0], p.fd_file_out, p.cmds[i]);
}

static void	close_and_wait(t_pipex p, pid_t *pids)
{
	int	i;

	close(p.pipe_fd[0]);
	close(p.pipe_fd[1]);
	close(p.fd_file_in);
	i = 0;
	while (i < p.cmds_len)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	close(p.fd_file_out);
	free(pids);
}

void	ft_manage_threads(t_pipex p)
{
	pid_t	*pids;
	int		i;

	pids = malloc(sizeof(pid_t) * p.cmds_len);
	if (!pids)
		return (ft_malloc_error());
	i = -1;
	while (++i < p.cmds_len)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (ft_fork_error(pids));
		if (pids[i] == 0)
		{
			if (i == 0)
				ft_thread_in(p, i);
			else if (i == p.cmds_len - 1)
				ft_thread_out(p, i);
			else
				ft_thread(p.pipe_fd[0], p.pipe_fd[1], p.cmds[i]);
		}
	}
	close_and_wait(p, pids);
}
