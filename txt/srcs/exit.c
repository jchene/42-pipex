/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:14:18 by jchene            #+#    #+#             */
/*   Updated: 2022/05/02 19:31:35 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	experror(const char *msg)
{
	perror(msg);
	return (-1);
}

int	exit_all(t_exec *struc, unsigned int ret)
{
	close(struc->fds[0]);
	close(struc->fds[1]);
	close(struc->pipe_ends[0]);
	close(struc->pipe_ends[1]);
	free_split(struc->splits[0]);
	free_split(struc->splits[1]);
	free(struc->paths[0]);
	free(struc->paths[1]);
	return (ret);
}
