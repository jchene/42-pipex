/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/13 15:55:23 by jchene           ###   ########.fr       */
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

int	child_process(t_exec2 struc, char **envp)
{
	dup2(struc.input_fd, STDIN_FILENO);
	if (struc.write_fd > 0)
		close(struc.write_fd);
	dup2(struc.output_fd, STDOUT_FILENO);
	if (struc.read_fd > 0)
		close(struc.read_fd);
	fprint("PATH:", 3);
	fprint(struc.path, 3);
	fprint("\n", 3);
	if (execve(struc.path, struc.args, envp) < 0)
		perror("Execve Error");
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec2			struc;
	pid_t			*ids;
	int				pipe_ends[2];
	int				i;

	if (argc < 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	if (!nul((void **)&ids, sizeof(pid_t) * (argc - 3)))
		return (-1);
	printf("argc:%d\n", argc);
	i = 2;
	while (i < argc - 1)
	{
		if (i == 2)
		{
			struc.input_fd = open(argv[1], O_RDONLY);
			if (struc.input_fd < 0)
				return (iperror("Error while opening infile: ", -1));
			struc.write_fd = -1;
		}
		else
		{
			struc.input_fd = pipe_ends[READ];
			struc.write_fd = pipe_ends[WRITE];
		}
		if (i == argc - 2)
		{
			if (!access(argv[argc - 1], W_OK))
				if (unlink(argv[argc - 1]))
					return (iperror("Error while unlinking outfile: ", -1));
			struc.output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 00777);
			if (struc.output_fd < 0)
				return (iperror("Error while opening outfile: ", -1));
			struc.read_fd = -1;
		}
		else
		{
			pipe(pipe_ends);
			struc.output_fd = pipe_ends[WRITE];
			struc.read_fd = pipe_ends[READ];
		}
		struc.args = split(argv[i], " \t");
		if (!struc.args)
			return (-1);
		if (get_path(&(struc.path), struc.args[0], envp) == -1)
			return (-1);
		ids[i - 2] = fork();
		if (ids[i - 2] < 0)
			return (iperror("Error while forking process: ", -1));
		if (!ids[i - 2])
			return (child_process(struc, envp));
		close(pipe_ends[READ]);
		close(pipe_ends[WRITE]);
		i++;
	}
	i = 0;
	while (i < argc - 2)
	{
		waitpid(ids[i], NULL, 0);
		i++;
	}
	return (0);
}

int	main2(int argc, char **argv, char **envp)
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
