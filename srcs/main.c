/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/12 19:00:22 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	child1_process(t_exec *struc, char **envp)
{
	dup2(struc->fds[CHILD1], STDIN_FILENO);
	dup2(struc->pipe_ends[WRITE], STDOUT_FILENO);
	close(struc->pipe_ends[READ]);
	if (execve(struc->paths[CHILD1], struc->splits[CHILD1], envp) < 0)
		perror("Child process 1 execve error: ");
	return (-1);
}

int	child2_process(t_exec *struc, char **envp)
{
	dup2(struc->fds[CHILD2], STDOUT_FILENO);
	dup2(struc->pipe_ends[READ], STDIN_FILENO);
	close(struc->pipe_ends[WRITE]);
	if (execve(struc->paths[CHILD2], struc->splits[CHILD2], envp) < 0)
		perror("Child process 2 execve error: ");
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	struc;

	if (argc != 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	if (parse_args(&struc, argv, envp) == -1)
		return (-1);
	pipe(struc.pipe_ends);
	struc.id[CHILD1] = fork();
	if (struc.id[CHILD1] < 0)
		return (iperror("Error while forking process: ", -1));
	if (!struc.id[CHILD1])
		return (child1_process(&struc, envp));
	struc.id[CHILD2] = fork();
	if (struc.id[CHILD2] < 0)
		return (iperror("Error while forking process: ", -1));
	if (!struc.id[CHILD2])
		return (child2_process(&struc, envp));
	close(struc.pipe_ends[READ]);
	close(struc.pipe_ends[WRITE]);
	waitpid(struc.id[CHILD1], NULL, 0);
	waitpid(struc.id[CHILD2], NULL, 0);
	return (exit_all(&struc, 0));
}
