/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:57:40 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/24 10:46:16 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_fork_error(pid_t *pids)
{
	perror("Error: fork failed\n");
	free(pids);
}

void	ft_open_error(char *file)
{
	int	i;

	write(2, "pipex: ", 7);
	i = 0;
	while (file[i])
		i++;
	write(2, file, i);
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	ft_malloc_error(void)
{
	write(2, "Error: malloc failed\n", 21);
	exit(1);
}

void	ft_cmd_error(char *cmd)
{
	write(2, "pipex: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Command not found\n", 20);
}
