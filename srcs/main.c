/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/07 18:13:25 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	child1_process(t_exec *struc, char *argv2, char **envp)
{
	struc->splits[0] = split(argv2, " \t");
	if (!struc->splits[0])
		return (-1);
	struc->paths[0] = NULL;
	if (get_path(&(struc->paths[0]), struc->splits[0][0], envp) == -1)
		return (-1);
	fprint("Cmd1 path: ", 1);
	fprint(struc->paths[0], 1);
	fprint("\n", 1);
	/*dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_ends[WRITE], STDOUT_FILENO);
	close(pipe_ends[READ]);
	close(infile_fd);*/
	//execve(struc->paths[0], struc->splits[0], envp);
	return (0);
}

int	child2_process(t_exec *struc, char *argv3, char **envp)
{
	struc->splits[1] = split(argv3, " \t");
	if (!struc->splits[1])
		return (-1);
	struc->paths[1] = NULL;
	if (get_path(&(struc->paths[1]), argv3, envp) == -1)
		return (-1);
	fprint("Cmd2 path: ", 1);
	fprint(struc->paths[1], 1);
	fprint("\n", 1);
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
	struc.id[CHILD1] = fork();
	if (struc.id[CHILD1] < 0)
		return (iperror("Error when forking child 1: ", -1));
	if (!struc.id[CHILD1])
		return (child1_process(&struc, argv[2], envp));
	struc.id[CHILD2] = fork();
	if (struc.id[CHILD2] < 0)
		return (iperror("Error when forking child 2: ", -1));
	if (!struc.id[CHILD2])
		return (child2_process(&struc, argv[3], envp));
	waitpid(struc.id[CHILD1], NULL, 0);
	waitpid(struc.id[CHILD2], NULL, 0);
	return (0);
}
