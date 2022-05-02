/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/02 14:42:55 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	parse_args(char **argv, int fds[2])
{
	fds[INFILE] = open(argv[1], O_RDONLY);
	if (fds[INFILE] == 0)
		return (-1);
	fds[OUTFILE] = open(argv[1], O_WRONLY | O_CREAT);
	if (fds[OUTFILE] == 0)
		return (-1);
	return (0);
}

int	child1_process(int infile_fd, int *pipe_ends, char *cmd, char **envp)
{
	char	**args;

	args = split(cmd, " \t");
	if (!args)
		return (-1);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_ends[WRITE], STDOUT_FILENO);
	close(pipe_ends[READ]);
	close(infile_fd);
	execve(args[0], args, envp);
	return (0);
}

int	child2_process(int outfile_fd, int *pipe_ends, char *cmd, char **envp)
{
	char	**args;

	args = split(cmd, " \t");
	if (!args)
		return (-1);
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(pipe_ends[READ], STDIN_FILENO);
	close(pipe_ends[WRITE]);
	close(outfile_fd);
	execve(args[0], args, envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];
	int		pipe_ends[2];
	pid_t	id[2];

	if (argc != 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	if (parse_args(argv, &fds) == -1)
		return (experror("Parse Error: "));
	pipe(pipe_ends);
	id[0] = fork();
	if (id[0] < 0)
		return (experror("Fork Error: "));
	if (!id[0])
		return (child1_process(fds[INFILE], pipe_ends, argv[2], envp));
	id[1] = fork();
	if (id[1] < 0)
		return (experror("Fork Error: "));
	waitpid(id[0], NULL, 0);
	if (!id[1])
		return (child2_process(fds[OUTFILE], pipe_ends, argv[4], envp));
	waitpid(id[1], NULL, 0);
	return (0);
}
