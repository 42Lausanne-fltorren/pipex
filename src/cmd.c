/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:51:56 by fltorren          #+#    #+#             */
/*   Updated: 2024/01/25 15:27:52 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_get_env(char *name, char **envp)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0)
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*ft_join_cmd(char *cmd, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(tmp, cmd);
	if (!tmp2)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (tmp2);
}

static char	*ft_get_cmd_path(char *cmd, char *path)
{
	char	**split;
	size_t	i;
	char	*tmp;

	split = ft_split(path, ':');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		tmp = ft_join_cmd(cmd, split[i]);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0)
		{
			ft_free_arr(split);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	ft_free_arr(split);
	return (NULL);
}

/*
	Takes a string from the command input
	Splits it into a command and all its arguments
	Adds the PATH to the command
	Returns the command with its arguments

	Eg. "ls -l" -> ["/bin/ls', "-l", NULL];
	Eg. "awk ''{count++} END {print count}''"
			-> ["/usr/bin/awk", "''{count++} END {print count}''", NULL];
*/
char	**ft_parse_cmd(char *arg, char **envp)
{
	char	**split;
	char	*path;
	char	*cmd;

	split = ft_custom_split(arg, ' ');
	if (!split)
		return (NULL);
	path = ft_get_env("PATH", envp);
	if (!path)
	{
		ft_free_arr(split);
		return (NULL);
	}
	cmd = ft_get_cmd_path(split[0], path);
	if (!cmd)
	{
		ft_free_arr(split);
		return (NULL);
	}
	free(split[0]);
	split[0] = cmd;
	return (split);
}
