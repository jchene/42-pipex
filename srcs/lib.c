/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:26:14 by jchene            #+#    #+#             */
/*   Updated: 2022/04/30 18:15:08 by jchene           ###   ########.fr       */
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

char	**split(char *str, const char *delims)
{
	char			**tab;
	unsigned int	i;
	unsigned int	ndelim;

	i = 0;
	ndelim = 0;
	while (str[i])
		if (is_charset(delims, str[i++]))
			ndelim++;
	tab = malloc(sizeof(char *) * ndelim);
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i] && !is_charset(delims, str[i]))
		
	return (tab);
}
