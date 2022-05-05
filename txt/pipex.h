/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:16 by jchene            #+#    #+#             */
/*   Updated: 2022/05/02 19:32:53 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define READ		0
# define WRITE		1
# define INFILE 	0
# define OUTFILE	1

typedef struct s_exec
{
	int		pipe_ends[2];
	int		fds[2];
	pid_t	id[2];
	char	**splits[2];
	char	*paths[2];
}				t_exec;

//LIB
unsigned int	ft_strlen(const char *str);
unsigned int	is_charset(const char *charset, char c);
void			ft_strcpyl(char *src, char *dst, unsigned int length);
unsigned int	get_nb_words(const char *delims, char *str);
char			**split(char *str, const char *delims);

//PARSING
int				parse_args(char **argv, int fds[2]);

//MEMORY
void			*ft_calloc(size_t size);
void			free_splitn(char **tab, unsigned int nword);
void			free_split(char **tab);

//EXIT
int				experror(const char *msg);
int				exit_all(t_exec *struc, unsigned int ret);

//PRINT
void			fprint(const char *str, int fd);
int				fexprint(char *str, int fd, int ret);

#endif