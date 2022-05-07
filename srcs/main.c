/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/07 15:34:38 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	child1_process(t_exec *struc, char *cmd, char **envp)
{
	struc->splits[0] = split(cmd, " \t");
	if (!struc->splits[0])
		return (-1);
	if (get_path(struc->paths[0], cmd, envp) == -1)
		return (-1);
	/*dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_ends[WRITE], STDOUT_FILENO);
	close(pipe_ends[READ]);
	close(infile_fd);*/
	//execve(struc->paths[0], struc->splits[0], envp);
	return (0);
}

int	child2_process(t_exec *struc, char *cmd, char **envp)
{
	struc->splits[1] = split(cmd, " \t");
	if (!struc->splits[1])
		return (-1);
	(void)envp;
	/*if (get_path(struc->paths[1], cmd, envp) == -1)
		return (-1);*/
	/*dup2(outfile_fd, STDOUT_FILENO);
	dup2(pipe_ends[READ], STDIN_FILENO);
	close(pipe_ends[WRITE]);
	close(outfile_fd);*/
	//execve(struc->paths[1], struc->splits[1], envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	struc;

	if (argc != 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	if (parse_args(argv, &(struc.fds[0])) == -1)
		return (-1);
	pipe(struc.pipe_ends);
	struc.id[0] = fork();
	if (struc.id[0] < 0)
		return (iperror("Error when forking child 1: ", -1));
	if (!struc.id[0])
		return (child1_process(&struc, argv[2], envp));
	struc.id[1] = fork();
	if (struc.id[1] < 0)
		return (iperror("Error when forking child 2: ", -1));
	if (!struc.id[1])
		return (child2_process(&struc, argv[3], envp));
	waitpid(struc.id[0], NULL, 0);
	waitpid(struc.id[1], NULL, 0);
	return (0);
}
