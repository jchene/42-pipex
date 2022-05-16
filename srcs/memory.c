/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:15:57 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 00:15:46 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//allocate *ptr_addr and fill it with 0's	//return *ptr_addr or NULL
void	*nul(void **ptr_addr, size_t size)
{
	size_t	i;

	if (!size)
		return (NULL);
	(*ptr_addr) = (void *)malloc(size);
	if (!(*ptr_addr))
		return (pperror("Malloc Error: ", NULL));
	i = 0;
	while (i < size)
	{
		((unsigned char *)(*ptr_addr))[i] = 0;
		i++;
	}
	return (*ptr_addr);
}

//allocate *dst_addr and copies src into it	//return *dst_addr or NULL 
void	*ft_strdup(char *src, char **dst_addr)
{
	if (!nul((void **)dst_addr, strl(src) + 1))
		return (NULL);
	ft_strcpyl(src, (*dst_addr), strl(src));
	return (*dst_addr);
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

void	free_struc(t_exec1 *struc)
{
	unsigned int	i;
	size_t			j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < get_nword(" \t", struc->cmds[i]))
		{
			free(struc->splits[i][j]);
			j++;
		}
		i++;
	}
}
