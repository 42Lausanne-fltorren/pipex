/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:34:53 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/24 10:27:47 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# ifndef BONUS
#  define BONUS 0
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft.h"
# include "stdio.h"
# include <errno.h>

typedef struct s_pipex
{
	int		pipe_fd[2];
	char	***cmds;
	int		cmds_len;
	int		fd_file_in;
	int		fd_file_out;
	char	**envp;
	char	**argv;
	int		argc;
}			t_pipex;

char	**ft_parse_cmd(char *arg, char **envp);
void	ft_free_arr(char **arr);

void	ft_manage_threads(t_pipex pipex);
char	**ft_custom_split(char *str, char c);

void	ft_malloc_error(void);
void	ft_fork_error(pid_t *pids);
void	ft_open_error(char *file);
void	ft_cmd_error(char *cmd);

#endif
