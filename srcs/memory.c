/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:15:57 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 16:42:27 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//allocate *ptr_addr and fill it with 0'	//returns *ptr_addr or NULL
void	*nul(void **ptr_addr, size_t size)
{
	size_t	i;

	if (!size)
		return (NULL);
	(*ptr_addr) = (void *)malloc(size);
	if (!(*ptr_addr))
		return (pperror("pipex: malloc", NULL));
	i = 0;
	while (i < size)
	{
		((unsigned char *)(*ptr_addr))[i] = 0;
		i++;
	}
	return (*ptr_addr);
}

//allocate *dst_addr and copies src into it	//returns *dst_addr or NULL 
void	*ft_strdup(char *src, char **dst_addr)
{
	if (!nul((void **)dst_addr, strl(src) + 1))
		return (NULL);
	ft_strcpyl(src, (*dst_addr), strl(src));
	return (*dst_addr);
}

//free the size first elements of tab
void	free_tab(void **tab, size_t size)
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

int	free_data(int i, int ret)
{
	int	j;

	j = 0;
	free(get_data(NULL)->ids);
	while (j < i)
	{
		free(get_data(NULL)->pipes[j]);
		j++;
	}
	free(get_data(NULL)->pipes);
	return (ret);
}

int	free_exec(int ret)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = get_exec(NULL);
	while (exec->args[i])
	{
		free(exec->args[i]);
		i++;
	}
	free(exec->args[i]);
	free(exec->args);
	free(exec->path);
	return (ret);
}
