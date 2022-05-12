/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/12 15:13:03 by jchene           ###   ########.fr       */
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
	dup2(struc->fds[CHILD1], STDIN_FILENO);
	close(struc->pipe_ends[READ]);
	dup2(struc->pipe_ends[WRITE], STDOUT_FILENO);
	if (execve(struc->paths[CHILD1], struc->splits[CHILD1], envp) < 0)
		perror("Child process 1 execve error: ");
	return (exit_all(struc, CHILD1, -1));
}

int	child2_process(t_exec *struc, char **envp)
{
	struc->splits[CHILD2] = split(struc->cmds[CHILD2], " \t");
	if (!struc->splits[CHILD2])
		return (-1);
	struc->paths[CHILD2] = NULL;
	if (get_path(&(struc->paths[CHILD2]), struc->splits[CHILD2][0], envp) == -1)
		return (-1);
	//dup2(struc->fds[CHILD2], STDOUT_FILENO);
	close(struc->pipe_ends[WRITE]);
	dup2(struc->pipe_ends[READ], STDIN_FILENO);
	if (execve(struc->paths[CHILD2], struc->splits[CHILD2], envp) < 0)
		perror("Child process 2 execve error: ");
	return (exit_all(struc, CHILD2, -1));
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	struc;

	if (argc != 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	if (parse_args(argv, &(struc.fds[0])) == -1)
		return (-1);
	pipe(struc.pipe_ends);
	struc.std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	struc.std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
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
	return (close_all(&struc, 0));
}
