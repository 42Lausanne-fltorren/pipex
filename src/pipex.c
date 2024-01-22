/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:29:42 by fltorren          #+#    #+#             */
/*   Updated: 2024/01/22 14:49:15 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_init(int argc, char **argv, t_pipex *data)
{
	if (argc != 5)
	{
		perror("Error: wrong number of arguments\n");
		return (0);
	}
	if (pipe(data->pipe_fd) == -1)
	{
		perror("Error: pipe failed\n");
		return (0);
	}
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in == -1)
	{
		perror("Error: open failed\n");
		return (0);
	}
	data->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (data->fd_out == -1)
	{
		perror("Error: open failed\n");
		return (0);
	}
	ft_parse_cmd(argv[2], &data->cmd1, data->envp);
	ft_parse_cmd(argv[3], &data->cmd2, data->envp);
	return (data->cmd1 && data->cmd2);
}

static void	ft_free_data(t_pipex *data)
{
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	if (data->cmd1)
		free(data->cmd1);
	if (data->cmd2)
		free(data->cmd2);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;
	pid_t	pids[2];

	data.envp = envp;
	if (ft_init(argc, argv, &data))
	{
		pids[0] = fork();
		if (pids[0] < 0)
		{
			perror("Error: fork failed\n");
			return (1);
		}
		if (pids[0] == 0)
			ft_in_child(&data, argv[2]);
		pids[1] = fork();
		if (pids[1] < 0)
		{
			perror("Error: fork failed\n");
			return (1);
		}
		if (pids[1] == 0)
			ft_out_child(&data, argv[3]);
		ft_free_data(&data);
		waitpid(pids[0], NULL, 0);
		waitpid(pids[1], NULL, 0);
	}
	return (0);
}
