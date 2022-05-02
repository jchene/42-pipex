/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:26:14 by jchene            #+#    #+#             */
/*   Updated: 2022/05/02 19:29:34 by jchene           ###   ########.fr       */
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

unsigned int	get_nb_words(const char *delims, char *str)
{
	unsigned int	i;
	unsigned int	nword;

	i = 0;
	nword = 0;
	while (str[i])
		if (is_charset(delims, str[i++]))
			if (str[i] && !is_charset(delims, str[i]))
				nword++;
	printf("delims: %d\n", nword);
	return (nword);
}

char	**split(char *str, const char *delims)
{
	char			**tab;
	unsigned int	i;
	unsigned int	size;
	unsigned int	nword;

	tab = ft_calloc(sizeof(char *) * get_nb_words(delims, str) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	nword = 0;
	while (str[i])
	{
		size = 0;
		while (str[i] && is_charset(delims, str[i]))
			i++;
		while (str[i] && !is_charset(delims, str[i++]))
			size++;
		tab[nword] = ft_calloc(sizeof(char) * size + 1);
		if (!tab[nword])
			free_splitn(tab, nword);
		ft_strcpyl(&(str[i - size]), tab[nword], size);
		nword++;
	}
	tab[nword] = NULL;
	return (tab);
}
