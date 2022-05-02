/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:15:57 by jchene            #+#    #+#             */
/*   Updated: 2022/05/02 14:38:39 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_calloc(size_t size)
{
	size_t	i;
	void	*mem_addr;

	if (!size)
		return (NULL);
	mem_addr = (void *)malloc(size);
	if (!mem_addr)
		return (NULL);
	i = 0;
	while (i < size)
		((unsigned char *)mem_addr)[i++] = 0;
	return (mem_addr);
}

void	free_split(char **tab, unsigned int nword)
{
	unsigned int	i;

	i = 0;
	while (i < nword)
	{
		free(tab[nword]);
		i++;
	}
	free(tab);
}
