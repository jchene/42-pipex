/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:07:05 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 02:42:21 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

unsigned int	get_nword(const char *delims, char *str)
{
	unsigned int	i;
	unsigned int	nword;

	i = 0;
	nword = 0;
	while (str[i])
	{
		while (str[i] && is_charset(delims, str[i]))
			i++;
		if (str[i])
				nword++;
		while (str[i] && !is_charset(delims, str[i]))
			i++;
	}
	return (nword);
}

#define I		0
#define SIZE 	1
#define NWORD 	2

char	**split(char *str, const char *delims)
{
	char			**tab;
	unsigned int	c[3];

	if (!nul((void **)&tab, sizeof(char *) * (get_nword(delims, str) + 1)))
		return (NULL);
	c[I] = 0;
	c[NWORD] = 0;
	while (str[c[I]])
	{
		c[SIZE] = 0;
		while (str[c[I]] && is_charset(delims, str[c[I]]))
			c[I]++;
		while (str[c[I]] && !is_charset(delims, str[c[I]]))
		{
			c[I]++;
			c[SIZE]++;
		}
		if (!nul((void **)&(tab[c[NWORD]]), sizeof(char) * (c[SIZE] + 1)))
			free_tab(tab, c[NWORD]);
		ft_strcpyl(&(str[c[I] - c[SIZE]]), tab[c[NWORD]], c[SIZE]);
		c[NWORD]++;
	}
	tab[c[NWORD]] = NULL;
	return (tab);
}
