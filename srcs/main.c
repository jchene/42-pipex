/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/04/30 22:05:36 by jchene           ###   ########.fr       */
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

int	child_process(int infile_fd, int *pipe_ends, char *cmd, char **envp)
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
}

int	parent_process(int outfile_fd, int *pipe_ends, char *cmd, pid_t *pid, char **envp)
{
	char	**args;

	args = split(cmd, " \t");
	if (!args)
		return (-1);
	waitpid(-1, pid, 0);
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(pipe_ends[READ], STDIN_FILENO);
	close(pipe_ends[WRITE]);
	close(outfile_fd);
	execve(args[0], args, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];
	int		pipe_ends[2];
	pid_t	id;

	if (argc != 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	if (parse_args(argv, &fds) == -1)
		return (experror("Parse Error: "));
	pipe(pipe_ends);
	id = fork();
	if (id < 0)
		return (experror("Fork Error: "));
	if (!id)
		child_process(fds[INFILE], pipe_ends, argv[2], envp);
	else
		parent_process(fds[OUTFILE], pipe_ends, argv[4], &id, envp);
	return (0);
}
