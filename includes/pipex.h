/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:34:53 by fltorren          #+#    #+#             */
/*   Updated: 2024/01/11 14:50:58 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft.h"
# include "stdio.h"

typedef struct s_pipex
{
	int		pipe_fd[2];
	char	*cmd1;
	char	*cmd2;
	int		fd_in;
	int		fd_out;
	char	**envp;
	char	**args;
}			t_pipex;

void	ft_parse_cmd(char *str, char **out, char **envp);
void	ft_free_arr(char **arr);

void	ft_in_child(t_pipex *pipex, char *cmd);
void	ft_out_child(t_pipex *pipex, char *cmd);
char	**ft_parse_cmd_args(char *cmd);
#endif
