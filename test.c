/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:54:54 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 01:13:22 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

#define LELOL	"pipex:"

int	main(int argc, char **argv, char **envp)
{
	char	**args;
	char	*path;
	int		fd;
	const char	tt[5] = "caca";

	(void)argc;
	(void)argv;
	nul((void **)&args, sizeof(char *) * 3);
	ft_strdup("cat", &args[0]);
	//ft_strdup("caca", &args[1]);
	fd = open(tt, O_RDONLY);
	if (fd < 0)
	{
		perror(LELOL);
		return (-1);
	}
	get_path(&path, "cat", envp);
	dup2(fd, STDIN_FILENO);
	execve(path, args, envp);
	return (0);
}
