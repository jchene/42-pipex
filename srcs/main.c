/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 00:23:12 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	child_process2(t_exec exec, char **envp)
{
	dup2(exec.input_fd, STDIN_FILENO);
	if (exec.write_fd > 0)
		close(exec.write_fd);
	dup2(exec.output_fd, STDOUT_FILENO);
	if (exec.read_fd > 0)
		close(exec.read_fd);
	if (execve(exec.path, exec.args, envp) < 0)
		perror("Execve Error");
	return (-1);
}

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

/*if (!access(argv[argc - 1], W_OK))
		if (unlink(argv[argc - 1]))
			return (iperror("Error while unlinking outfile: ", -1));
	data->file_fds[OUTFILE] = open(argv[argc - 1], O_WRONLY | O_CREAT, 00777);*/

int	main1(int argc, char **argv, char **envp)
{
	t_exec	exec;
	t_data	data;
	int		i;

	if (argc < 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	if (init_data(&data, argc) == -1)
		return (-1);
	i = 0;
	while (i < argc - 3)
	{
		if (init_exec(&exec, argv, envp, i) == -1)
			return (-1);
		data.ids[i] = fork();
		if (data.ids[i] < 0)
			return (iperror("Error while forking process: ", -1));
		if (!data.ids[i])
			return (child_process(exec, envp));
		i++;
	}
	close_fds(data);
	wait_all(data);
	return (0);
}
