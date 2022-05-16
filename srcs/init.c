/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:49:13 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 00:15:53 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	init_data(t_data *data, int argc)
{
	int		i;

	if (!nul((void **)data->ids, sizeof(pid_t) * ((argc - 3) + 1)))
		return (-1);
	if (!nul((void **)data->pipes, sizeof(int [2]) * ((argc - 3) + 1)))
	{
		free(data->ids);
		return (-1);
	}
	i = 0;
	while (i < argc - 3)
	{
		data->pipes[i][READ] = -1;
		data->pipes[i][WRITE] = -1;
		data->ids[i] = -1;
		i++;
	}
	data->files_fds[0] = -1;
	data->files_fds[1] = -1;
	return (0);
}

int	set_fds(t_exec *exec, char **argv, int i)
{
	if (i == 1)
	{
		exec->in_fds[READ] = open(argv[1], O_RDONLY);
		if (exec->in_fds[READ] < 0)
			perror()
	}
	return (0);
}

int	init_exec(t_exec *exec, char **argv, char **envp, int i)
{
	if (set_fds(&exec, argv, i) == -1)
		return (-1);
	if (get_args(exec, argv, i) == -1)
		return (-1);
	if (get_path(&(exec->path), exec->args[0], envp) == -1)
		return (-1);
	return (0);
}
