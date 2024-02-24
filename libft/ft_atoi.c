/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:41:32 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/11 11:13:26 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

static int	ft_isnbr(char c)
{
	return (c >= '0' && c <= '9');
}

static unsigned int	ft_strtonbr(const char *str)
{
	unsigned int	n;

	n = 0;
	while (*str && ft_isnbr(*str))
	{
		n = 10 * n + (*str - '0');
		str++;
	}
	return (n);
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	nbr;

	while (*str && ft_isspace(*str))
		str++;
	sign = 1;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nbr = ft_strtonbr(str);
	return (sign * nbr);
}
