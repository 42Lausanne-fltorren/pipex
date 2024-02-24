/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:29:42 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/24 10:51:39 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_parse_cmds(char **argv, int argc, char *envp[], char ***cmds)
{
	int	i;

	i = 2;
	while (i < argc - 1)
	{
		cmds[i - 2] = ft_parse_cmd(argv[i], envp);
		if (!cmds[i - 2])
			ft_cmd_error(argv[i]);
		i++;
	}
}

int	ft_open(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		ft_open_error(file);
	return (fd);
}

int	main(int argc, char **argv, char *envp[])
{
	char	***cmds;
	t_pipex	data;

	if (argc != 5 && !(argc > 5 && BONUS))
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	cmds = malloc(sizeof(char **) * argc - 3);
	if (!cmds)
	{
		write(2, "Error: malloc failed\n", 21);
		return (1);
	}
	data.fd_file_in = ft_open(argv[1], O_RDONLY, 0);
	data.fd_file_out = ft_open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
			0666);
	ft_parse_cmds(argv, argc, envp, cmds);
	data.cmds = cmds;
	data.cmds_len = argc - 3;
	data.argv = argv;
	data.argc = argc;
	pipe(data.pipe_fd);
	ft_manage_threads(data);
	return (0);
}
