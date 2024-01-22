/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:50:00 by fltorren          #+#    #+#             */
/*   Updated: 2024/01/11 15:10:35 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_parse_cmd_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		return (NULL);
	return (args);
}

void	ft_in_child(t_pipex *pipex, char *cmd)
{
	char	**args;

	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	dup2(pipex->fd_in, STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->fd_in);
	args = ft_parse_cmd_args(cmd);
	if (!args)
	{
		perror("ft_parse_cmd_args");
		_exit(1);
	}
	execve(pipex->cmd1, args + 1, pipex->envp);
	ft_free_arr(args);
	perror("execve");
	_exit(1);
}

void	ft_out_child(t_pipex *pipex, char *cmd)
{
	char	**args;

	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->fd_out, STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	close(pipex->fd_out);
	args = ft_parse_cmd_args(cmd);
	if (!args)
	{
		perror("ft_parse_cmd_args");
		_exit(1);
	}
	execve(pipex->cmd2, args + 1, pipex->envp);
	perror("execve");
	_exit(1);
}
