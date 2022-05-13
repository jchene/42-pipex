/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:33:03 by jchene            #+#    #+#             */
/*   Updated: 2022/05/13 18:43:07 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	pre_init(t_exec1 *struc, char **argv)
{
	struc->std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	struc->std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	struc->cmds[CHILD1] = argv[2];
	struc->cmds[CHILD2] = argv[3];
}

int	parse_args(t_exec1 *struc, char **argv, char **envp)
{
	pre_init(struc, argv);
	struc->splits[CHILD1] = split(struc->cmds[CHILD1], " \t");
	if (!struc->splits[CHILD1])
		return (-1);
	struc->paths[CHILD1] = NULL;
	if (get_path(&(struc->paths[CHILD1]), struc->splits[CHILD1][0], envp) == -1)
		return (-1);
	struc->splits[CHILD2] = split(struc->cmds[CHILD2], " \t");
	if (!struc->splits[CHILD2])
		return (-1);
	struc->paths[CHILD2] = NULL;
	if (get_path(&(struc->paths[CHILD2]), struc->splits[CHILD2][0], envp) == -1)
		return (-1);
	struc->fds[INFILE] = open(argv[1], O_RDONLY);
	if (struc->fds[INFILE] < 0)
		return (iperror("Error while opening infile: ", -1));
	if (!access(argv[4], W_OK))
		if (unlink(argv[4]))
			return (iperror("Error while unlinking outfile: ", -1));
	struc->fds[OUTFILE] = open(argv[4], O_WRONLY | O_CREAT, 00777);
	if (struc->fds[OUTFILE] < 0)
		return (iperror("Error while opening outfile: ", -1));
	return (0);
}
