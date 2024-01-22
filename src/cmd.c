/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:35:51 by fltorren          #+#    #+#             */
/*   Updated: 2024/01/10 23:41:05 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_get_path_arr(char *envp[])
{
	int		i;
	char	**path_arr;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_arr = ft_split(envp[i] + 5, ':');
			return (path_arr);
		}
		i++;
	}
	return (NULL);
}

static char	*ft_parse_cmd_str(char *cmd_str)
{
	char	**split;
	char	*cmd;
	char	*tmp;

	split = ft_split(cmd_str, ' ');
	cmd = ft_strdup(split[0]);
	ft_free_arr(split);
	tmp = cmd;
	cmd = ft_strjoin("/", cmd);
	free(tmp);
	return (cmd);
}

void	ft_parse_cmd(char *cmd_str, char **out, char **envp)
{
	char	**path_arr;
	char	*cmd_path;
	char	*cmd;
	size_t	i;

	cmd = ft_parse_cmd_str(cmd_str);
	path_arr = ft_get_path_arr(envp);
	if (!path_arr || !cmd)
		return ;
	i = 0;
	while (path_arr[i])
	{
		cmd_path = ft_strjoin(path_arr[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			*out = cmd_path;
			break ;
		}
		else
			free(cmd_path);
		i++;
	}
	free(cmd);
	ft_free_arr(path_arr);
}
