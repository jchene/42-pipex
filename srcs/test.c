/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:48:06 by jchene            #+#    #+#             */
/*   Updated: 2022/05/02 15:16:31 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_path(char *cmd, char **envp)
{
	return (NULL);
}

int	child1(int pipe_ends[2], char **envp)
{
	char	*params[2];
	char	*word;

	(void)pipe_ends;
	word = ft_calloc(16);
	ft_strcpyl("./txt/input/txt", word, 15);
	//dup2(pipe_ends[WRITE], STDOUT_FILENO);
	//close(pipe_ends[READ]);
	execve(get_path("cat", envp), params, envp);
	return (1);
}

int	child2(int pipe_ends[2], char **envp)
{
	(void)envp;
	(void)pipe_ends;
	return (2);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	ids[2];
	int		pipe_ends[2];

	(void)argc;
	(void)argv;
	pipe(pipe_ends);
	ids[0] = fork();
	if (ids[0] < 0)
		return (experror("Fork Error: "));
	if (!ids[0])
		return (printf("ret: %d\n", child1(pipe_ends, envp)));
	waitpid(ids[0], NULL, 0);
	ids[1] = fork();
	if (ids[1] < 0)
		return (experror("Fork Error: "));
	if (!ids[1])
		return (printf("ret: %d\n", child2(pipe_ends, envp)));
	waitpid(ids[1], NULL, 0);
	return (printf("ret: %d\n", 0));
}
