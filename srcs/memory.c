/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:15:57 by jchene            #+#    #+#             */
/*   Updated: 2022/05/07 15:30:58 by jchene           ###   ########.fr       */
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

void	free_splitn(char **tab, unsigned int nword)
{
	unsigned int	i;

	i = 0;
	while (i < nword)
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
}
