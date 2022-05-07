/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:07:05 by jchene            #+#    #+#             */
/*   Updated: 2022/05/07 16:25:32 by jchene           ###   ########.fr       */
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
		if (is_charset(delims, str[i++]))
			if (str[i] && !is_charset(delims, str[i]))
				nword++;
	return (nword);
}

char	**split(char *str, const char *delims)
{
	char			**tab;
	unsigned int	i;
	unsigned int	size;
	unsigned int	nword;

	if (!mycalloc((void **)&(tab), sizeof(char *) * get_nword(delims, str) + 1))
		return (NULL);
	i = 0;
	nword = 0;
	while (str[i])
	{
		size = 0;
		while (str[i] && is_charset(delims, str[i]))
			i++;
		while (str[i] && !is_charset(delims, str[i]))
		{
			i++;
			size++;
		}
		if (!mycalloc((void **)&(tab[nword]), sizeof(char) * size + 1))
			free_tab(tab, nword);
		ft_strcpyl(&(str[i - size]), tab[nword], size);
		nword++;
	}
	return (tab);
}
