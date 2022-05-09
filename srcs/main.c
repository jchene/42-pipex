/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/09 19:18:10 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	child1_process(t_exec *struc, char **envp)
{
	struc->splits[CHILD1] = split(struc->cmds[CHILD1], " \t");
	if (!struc->splits[CHILD1])
		return (-1);
	struc->paths[CHILD1] = NULL;
	if (get_path(&(struc->paths[CHILD1]), struc->splits[CHILD1][0], envp) == -1)
		return (-1);
	printf("[%d]CHILD1 cmd path: %s\n", getpid(), struc->paths[CHILD1]);
	free_tab(struc->splits[0], get_nword(" \t", struc->cmds[0]) + 1);
	free(struc->paths[0]);
	return (close_all(struc, 0));
}

int	child2_process(t_exec *struc, char **envp)
{
	struc->splits[CHILD2] = split(struc->cmds[CHILD2], " \t");
	if (!struc->splits[CHILD2])
		return (-1);
	struc->paths[CHILD2] = NULL;
	if (get_path(&(struc->paths[CHILD2]), struc->splits[CHILD2][0], envp) == -1)
		return (-1);
	printf("[%d]CHILD2 cmd path: %s\n", getpid(), struc->paths[CHILD2]);
	free_tab(struc->splits[1], get_nword(" \t", struc->cmds[1]) + 1);
	free(struc->paths[1]);
	return (close_all(struc, 0));
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	struc;

	if (argc != 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	if (parse_args(argv, &(struc.fds[0])) == -1)
		return (-1);
	pipe(struc.pipe_ends);
	struc.cmds[CHILD1] = argv[2];
	struc.cmds[CHILD2] = argv[3];
	struc.id[CHILD1] = fork();
	if (struc.id[CHILD1] < 0)
		return (iperror("Error when forking child 1: ", -1));
	if (!struc.id[CHILD1])
		return (child1_process(&struc, envp));
	waitpid(struc.id[CHILD1], NULL, 0);
	struc.id[CHILD2] = fork();
	if (struc.id[CHILD2] < 0)
		return (iperror("Error when forking child 2: ", -1));
	if (!struc.id[CHILD2])
		return (child2_process(&struc, envp));
	waitpid(struc.id[CHILD2], NULL, 0);
	free_struc(&struc);
	return (close_all(&struc, 0));
}
