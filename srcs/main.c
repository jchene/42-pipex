/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/18 19:17:24 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//saves data_init when called with argument	//return stored address
t_data	*get_data(t_data *data_init)
{
	static t_data	*data = NULL;

	if (data_init)
		data = data_init;
	return (data);
}

//saves exec_init when called with argument	//return stored address
t_exec	*get_exec(t_exec *exec_init)
{
	static t_exec	*exec = NULL;

	if (exec_init)
		exec = exec_init;
	return (exec);
}

int	child_process2(t_exec exec, char **envp)
{
	dup2(exec.in_fds[READ], STDIN_FILENO);
	if (exec.in_fds[WRITE] > 0)
		if (close(exec.in_fds[WRITE]))
			perror("pipex: close");
	dup2(exec.out_fds[WRITE], STDOUT_FILENO);
	if (exec.out_fds[READ] > 0)
		if (close(exec.out_fds[READ]))
			perror("pipex: close");
	if (execve(exec.path, exec.args, envp) < 0)
		perror("pipex: execve");
	return (-1);
}

int	child_process(t_exec exec, char **envp)
{
	fprintf(stderr, "%s[%d]%s - in: %d %d(x) out: %d(x) %d%s\n", GREEN, getpid(), exec.args[0], exec.in_fds[READ], exec.in_fds[WRITE], exec.out_fds[READ], exec.out_fds[WRITE], RESET);
	dup2(exec.in_fds[READ], STDIN_FILENO);
	if (exec.in_fds[WRITE] > 0)
	{
		fprintf(stderr, "%s[%d]closing: %d%s\n", GREEN, getpid(), exec.in_fds[WRITE], RESET);
		if (close(exec.in_fds[WRITE]))
			perror("pipex: close");
	}
	dup2(exec.out_fds[WRITE], STDOUT_FILENO);
	if (exec.out_fds[READ] > 0)
	{
		fprintf(stderr, "%s[%d]closing: %d%s\n", GREEN, getpid(), exec.out_fds[READ], RESET);
		if (close(exec.out_fds[READ]))
			perror("pipex: close");
	}
	fprintf(stderr, "%s[%d]path: |%s| cmd: |%s|%s\n", GREEN, getpid(), exec.path, exec.args[0], RESET);
	if (execve(exec.path, exec.args, envp) < 0)
		perror("pipex: execve");
	return (-1);
}

void	exit_test(int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		fprintf(stderr, "[%d]waiting for: %d\n", getpid(), get_data(NULL)->ids[j]);
		wait(NULL);
		j++;
	}
	j = 0;
	while (j < i)
	{
		close_pipes(j);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec;
	t_data	data;
	int		i;

	if (argc < 5)
		return (fexprint("pipex: Wrong number of arguments.\n", 2, -1));
	fprintf(stderr, "%s[%d]PID: main: %d%s\n", RED, getpid(), getpid(), RESET);
	if (init_data(&data, &exec, argc) == -1)
		return (-1);
	i = 0;
	while (i < argc - 3)
	{
		if (init_exec(argc, argv, envp, i) == -1)
			return (-1);
		data.ids[i] = fork();
		if (data.ids[i] < 0)
			return (iperror("pipex: fork", -1));
		if (!data.ids[i])
			return (child_process(exec, envp));
		else
			fprintf(stderr, "%s[%d]PID: child[%d]: %d%s\n", RED, getpid(), i, data.ids[i], RESET);
		free_exec(0);
		i++;
	}
	fprintf(stderr, "[%d]i: %d\n", getpid(), i);
	exit_test(i);
	close_fds();
	free_data(i, 0);
	return (0);
}
