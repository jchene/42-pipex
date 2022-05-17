/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 02:47:11 by jchene           ###   ########.fr       */
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
		close(exec.in_fds[WRITE]);
	dup2(exec.out_fds[WRITE], STDOUT_FILENO);
	if (exec.out_fds[READ] > 0)
		close(exec.out_fds[READ]);
	if (execve(exec.path, exec.args, envp) < 0)
		perror("Execve Error");
	return (-1);
}

void	wait_all(void)
{
	t_data	*data;
	int		i;

	i = 0;
	data = get_data(NULL);
	while (data->ids[i] > 0)
	{
		waitpid(data->ids[i], NULL, 0);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec;
	t_data	data;
	int		i;

	if (argc < 5)
		return (fexprint("Error: Wrong number of arguments.\n", 2, -1));
	if (init_data(&data, argc) == -1)
		return (-1);
	get_exec(&exec);
	i = 0;
	while (i < argc - 3)
	{
		if (init_exec(argc, argv, envp, i) == -1)
			return (-1);
		data.ids[i] = fork();
		if (data.ids[i] < 0)
			return (iperror("Error while forking process: ", -1));
		if (!data.ids[i])
			return (child_process(exec, envp));
		free_exec(0);
		i++;
	}
	free_data(i, 0);
	wait_all();
	return (0);
}
