/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:14:18 by jchene            #+#    #+#             */
/*   Updated: 2022/06/10 17:03:47 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	iperror(const char *msg, int ret)
{
	perror(msg);
	return (ret);
}

void	*pperror(const char *msg, void *ret)
{
	perror(msg);
	return (ret);
}

int	close_all(t_exec exec, int ret)
{
	if (exec.in_fds[WRITE] > 0)
		if (close(exec.in_fds[WRITE]))
			perror("pipex1: close");
	if (exec.in_fds[READ] > 0)
		if (close(exec.in_fds[READ]))
			perror("pipex2: close");
	if (exec.out_fds[WRITE] > 0)
		if (close(exec.out_fds[WRITE]))
			perror("pipex3: close");
	if (exec.out_fds[READ] > 0 && ret == -2)
		if (close(exec.out_fds[READ]))
			perror("pipex4: close");
	if (ret != -2)
	{
		if (close(1))
			perror("pipex5: close");
		if (close(0))
			perror("pipex6: close");
	}
	return (ret);
}

void	close_pipes(int j)
{
	if ((get_data(NULL))->pipes[j][READ] > 0)
		if (close((get_data(NULL))->pipes[j][READ]))
			perror("pipex: close");
	if ((get_data(NULL))->pipes[j][WRITE] > 0)
		if (close((get_data(NULL))->pipes[j][WRITE]))
			perror("pipex: close");
	j++;
}

void	close_fds(void)
{
	if ((get_data(NULL))->files_fds[INFILE] > 0)
		if (close((get_data(NULL))->files_fds[INFILE]))
			perror("pipex: close");
	if ((get_data(NULL))->files_fds[OUTFILE] > 0)
		if (close((get_data(NULL))->files_fds[OUTFILE]))
			perror("pipex: close");
}
