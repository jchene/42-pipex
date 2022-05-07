/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:15:57 by jchene            #+#    #+#             */
/*   Updated: 2022/05/07 18:10:48 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*mycalloc(void **ptr_addr, size_t size)
{
	size_t	i;

	if (!size)
		return (NULL);
	(*ptr_addr) = (void *)malloc(size);
	if (!(*ptr_addr))
		return (pperror("Malloc Error: ", NULL));
	i = 0;
	while (i < size)
		((unsigned char *)(*ptr_addr))[i++] = 0;
	return (*ptr_addr);
}

void	*ft_strdup(char *src, char **dst)
{
	if (!mycalloc((void **)dst, ft_strlen(src) + 1))
		return (NULL);
	ft_strcpyl(src, (*dst), ft_strlen(src));
	return (dst);
}

void	free_tab(char **tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_split(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}
