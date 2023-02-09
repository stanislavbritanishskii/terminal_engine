/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:44:04 by sbritani          #+#    #+#             */
/*   Updated: 2023/02/09 14:18:26 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

static int	int_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n / 10 || n % 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	rec(long n, int len, char *res)
{
	if (n < 10)
		res[len] = n + '0';
	else
	{
		res[len] = n % 10 + '0';
		rec(n / 10, len - 1, res);
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		size;
	long	nbr;

	len = 0;
	nbr = n;
	size = int_len(nbr);
	res = malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	else
	{
		if (nbr < 0)
		{
			res[len++] = '-';
			nbr *= -1;
		}
		rec(nbr, size -1, res);
	}
	res[size] = '\0';
	return (res);
}

char	*ft_str_join_free_first(char *str1, char *str2)
{
	char	*res;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	i = -1;
	if (str1)
	{
		while (str1[++i])
			res[i] = str1[i];
	}
	i = -1;
	if (str2)
	{
		while (str2[++i])
			res[i + len1] = str2[i];
	}
	res[len1 + len2] = '\0';
	free(str1);
	return (res);
}