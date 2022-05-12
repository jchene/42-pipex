/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:14:18 by jchene            #+#    #+#             */
/*   Updated: 2022/05/12 18:59:23 by jchene           ###   ########.fr       */
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

int	close_all(t_exec *struc, unsigned int ret)
{
	close(struc->fds[CHILD1]);
	close(struc->fds[CHILD2]);
	close(struc->std_fds[STDIN_FILENO]);
	close(struc->std_fds[STDOUT_FILENO]);
	return (ret);
}

int	exit_all(t_exec *struc, unsigned int ret)
{
	free_tab(struc->splits[CHILD1], get_nword(" \t", struc->cmds[CHILD1]) + 1);
	free_tab(struc->splits[CHILD2], get_nword(" \t", struc->cmds[CHILD2]) + 1);
	free(struc->paths[CHILD1]);
	free(struc->paths[CHILD2]);
	return (close_all(struc, ret));
}
