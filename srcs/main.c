/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/13 19:48:01 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*int	child1_process(t_exec *struc, char **envp)
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
}*/

int	child_process(t_exec exec, char **envp)
{
	fprintf(stderr, "%s[%d]fds: in|%d| wr|%d| out|%d| re|%d| %s\n", GREEN, getpid(), exec.input_fd, exec.write_fd, exec.output_fd, exec.read_fd, RESET);
	dup2(exec.input_fd, STDIN_FILENO);
	if (exec.write_fd > 0)
	{
		fprintf(stderr, "%s[%d]closing write end |%d|%s\n", GREEN, getpid(), exec.write_fd, RESET);
		close(exec.write_fd);
	}
	dup2(exec.output_fd, STDOUT_FILENO);
	if (exec.read_fd > 0)
	{
		fprintf(stderr, "%s[%d]closing read end |%d|%s\n", GREEN, getpid(), exec.read_fd, RESET);
		close(exec.read_fd);
	}
	fprintf(stderr, "%s[%d]PATH: %s\n%s", GREEN, getpid(), exec.path, RESET);
	unsigned int	i;
	i = 0;
	while (exec.args[i])
	{
		fprintf(stderr, "%s[%d]arg[%d]:|%s|%s\n", GREEN, getpid(), i, exec.args[i], RESET);
		i++;
	}
	if (execve(exec.path, exec.args, envp) < 0)
		perror("Execve Error");
	return (-1);
}

int	new_parse(t_data *data, int argc, char **argv)
{
	data->file_fds[INFILE] = open(argv[1], O_RDONLY);
	if (data->file_fds[INFILE] < 0)
		return (iperror("Error while opening infile: ", -1));
	if (!access(argv[argc - 1], W_OK))
		if (unlink(argv[argc - 1]))
			return (iperror("Error while unlinking outfile: ", -1));
	data->file_fds[OUTFILE] = open(argv[argc - 1], O_WRONLY | O_CREAT, 00777);
	if (data->file_fds[OUTFILE] < 0)
	{
		if (data->file_fds[INFILE])
			close(data->file_fds[INFILE]);
		return (iperror("Error while opening outfile: ", -1));
	}
	fprintf(stderr, "%s[%d]parse: in|%d| out|%d| %s\n", RED, getpid(), data->file_fds[INFILE], data->file_fds[OUTFILE], RESET);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec;
	t_data	data;
	int		i;

	if (argc < 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	fprintf(stderr, "%s[%d]argc: %d%s\n", RED, getpid(), argc, RESET);
	if (new_parse(&data, argc, argv) == -1)
		return (-1);
	if (!nul((void **)&data.ids, sizeof(pid_t) * (argc - 2)))
		return (-1);
	i = 2;
	while (i < argc - 1)
	{
		if (i > 2)
		{
			exec.input_fd = data.pipe_ends[READ];
			exec.write_fd = data.pipe_ends[WRITE];
		}
		else
		{
			exec.input_fd = data.file_fds[INFILE];
			exec.write_fd = -1;
		}
		if (i < argc - 2)
		{
			data.old_pipe[READ] = data.pipe_ends[READ];
			data.old_pipe[WRITE] = data.pipe_ends[WRITE];
			pipe(data.pipe_ends);
			close(data.old_pipe[READ]);
			close(data.old_pipe[WRITE]);
			fprintf(stderr, "%s[%d]new pipes: |%d| |%d|%s\n", RED, getpid(), data.pipe_ends[INFILE], data.pipe_ends[OUTFILE], RESET);
			exec.output_fd = data.pipe_ends[WRITE];
			exec.read_fd = data.pipe_ends[READ];
		}
		else
		{
			fprintf(stderr, "%s[%d]last elem and outfile fd: |%d|%s\n", RED, getpid(), data.file_fds[OUTFILE], RESET);
			exec.output_fd = data.file_fds[OUTFILE];
			exec.read_fd = -1;
		}
		exec.args = split(argv[i], " \t");
		if (!exec.args)
			return (-1);
		if (get_path(&(exec.path), exec.args[0], envp) == -1)
			return (-1);
		data.ids[i - 2] = fork();
		if (data.ids[i - 2] < 0)
			return (iperror("Error while forking process: ", -1));
		if (!data.ids[i - 2])
			return (child_process(exec, envp));
		fprintf(stderr, "%s[%d]closed pipes: |%d| |%d| in parent%s\n", RED, getpid(), data.pipe_ends[INFILE], data.pipe_ends[OUTFILE], RESET);
		i++;
	}
	close(data.old_pipe[READ]);
	close(data.old_pipe[WRITE]);
	close(data.pipe_ends[READ]);
	close(data.pipe_ends[WRITE]);
	fprintf(stderr, "%s[%d]closed all%s\n", RED, getpid(), RESET);
	i = 0;
	while (i < argc - 3)
	{
		fprintf(stderr, "%s[%d]waiting for data[%d]:|%d|%s\n", RED, getpid(), i, data.ids[i], RESET);
		waitpid(data.ids[i], NULL, 0);
		i++;
	}
	return (0);
}

/*int	main2(int argc, char **argv, char **envp)
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
}*/
