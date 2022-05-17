/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 16:45:04 by jchene           ###   ########.fr       */
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

int	child_process(t_exec exec, char **envp)
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

void	wait_all(int i)
{
	t_data	*data;
	int		j;

	j = 0;
	data = get_data(NULL);
	while (j < i)
	{
		waitpid(data->ids[j], NULL, 0);
		j++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec;
	t_data	data;
	int		i;

	if (argc < 5)
		return (fexprint("pipex: Wrong number of arguments.\n", 2, -1));
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
		free_exec(0);
		i++;
	}
	close_fds(i);
	wait_all(i);
	free_data(i, 0);
	return (0);
}
