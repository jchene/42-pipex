/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:14:18 by jchene            #+#    #+#             */
/*   Updated: 2022/05/19 16:08:22 by jchene           ###   ########.fr       */
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

void	close_pipes(int j)
{
	//fprintf(stderr, "%s[%d]closing: %d%s\n", RED, getpid(), get_data(NULL)->pipes[j][READ], RESET);
	if (get_data(NULL)->pipes[j][READ] > 0)
		if (close(get_data(NULL)->pipes[j][READ]))
			perror("pipex: close");
	//fprintf(stderr, "%s[%d]closing: %d%s\n", RED, getpid(), get_data(NULL)->pipes[j][WRITE], RESET);
	if (get_data(NULL)->pipes[j][WRITE] > 0)
		if (close(get_data(NULL)->pipes[j][WRITE]))
			perror("pipex: close");
	j++;
}

void	close_fds(void)
{
	//fprintf(stderr, "%s[%d]closing: %d%s\n", RED, getpid(), get_data(NULL)->files_fds[INFILE], RESET);
	if (get_data(NULL)->files_fds[INFILE] > 0)
		if (close(get_data(NULL)->files_fds[INFILE]))
			perror("pipex: close");
	//fprintf(stderr, "%s[%d]closing: %d%s\n", RED, getpid(), get_data(NULL)->files_fds[OUTFILE], RESET);
	if (get_data(NULL)->files_fds[OUTFILE] > 0)
		if (close(get_data(NULL)->files_fds[OUTFILE]))
			perror("pipex: close");
}
