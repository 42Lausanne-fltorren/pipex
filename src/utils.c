/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:38:56 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/04 15:56:22 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	ft_count_word(char *str, char c)
{
	int	i;
	int	count;
	int	quotes;
	int	double_quotes;

	i = 0;
	count = 0;
	quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == c && quotes == 0 && double_quotes == 0)
			count++;
		else if (str[i] == '\'')
			quotes = !quotes;
		else if (str[i] == '\"')
			double_quotes = !double_quotes;
		i++;
	}
	return (count + 1);
}

static int	ft_word_length(char *str, char c)
{
	int	i;
	int	quotes;
	int	double_quotes;

	i = 0;
	quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == c && quotes == 0 && double_quotes == 0)
			break ;
		else if (str[i] == '\'')
			quotes = !quotes;
		else if (str[i] == '\"')
			double_quotes = !double_quotes;
		i++;
	}
	return (i);
}

static char	*ft_custom_substr(char *str, int start, int len)
{
	char	*substr;
	int		i;

	if ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '\"' && str[len - 1] == '\"'))
	{
		start++;
		len -= 2;
	}
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	**ft_custom_split(char *str, char c)
{
	int		count;
	char	**arr;
	int		i;
	int		l;

	count = ft_count_word(str, c);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		l = ft_word_length(str, c);
		arr[i] = ft_custom_substr(str, 0, l);
		if (!arr[i])
		{
			ft_free_arr(arr);
			return (NULL);
		}
		str += l;
		while (*str == c)
			str++;
	}
	arr[count] = NULL;
	return (arr);
}
