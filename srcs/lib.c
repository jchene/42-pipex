/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:26:14 by jchene            #+#    #+#             */
/*   Updated: 2022/05/09 18:53:18 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

unsigned int	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

unsigned int	is_charset(const char *charset, char c)
{
	unsigned int	i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

void	ft_strcpyl(char *src, char *dst, unsigned int length)
{
	unsigned int	i;

	i = -1;
	while (++i < length)
		dst[i] = src[i];
}

unsigned int	basic_cmp(const char *str1, char *str2)
{
	unsigned int	i;

	i = 0;
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}
