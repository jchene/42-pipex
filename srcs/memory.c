/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:15:57 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 02:59:30 by jchene           ###   ########.fr       */
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
		return (pperror("Malloc Error: ", NULL));
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
	int		j;
	t_data	*data;

	j = 0;
	data = get_data(NULL);
	while (j <= i)
	{
		if (data->pipes[i][READ] > 0)
			close(data->pipes[i][READ]);
		if (data->pipes[i][WRITE] > 0)
			close(data->pipes[i][WRITE]);
		i++;
	}
	if (data->files_fds[INFILE] > 0)
		close(data->files_fds[INFILE]);
	if (data->files_fds[OUTFILE] > 0)
		close(data->files_fds[OUTFILE]);
	free(data->ids);
	free(data->pipes);
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
