/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:16 by jchene            #+#    #+#             */
/*   Updated: 2022/05/12 14:18:39 by jchene           ###   ########.fr       */
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
# define CHILD1		0
# define CHILD2		1

typedef struct s_exec
{
	int		std_fds[2];
	int		pipe_ends[2];
	int		fds[2];
	pid_t	id[2];
	char	*cmds[2];
	char	**splits[2];
	char	*paths[2];
}				t_exec;

//LIB
unsigned int	ft_strlen(const char *str);
unsigned int	is_charset(const char *charset, char c);
void			ft_strcpyl(char *src, char *dst, unsigned int length);
unsigned int	basic_cmp(const char *str1, char *str2);

//STRING
unsigned int	get_nword(const char *delims, char *str);
char			**split(char *str, const char *delims);

//PARSING
int				parse_args(char **argv, int fds[2]);

//PATH
char			*get_env(const char *key, char **envp);
int				get_path(char **struc_path, char *cmd, char **envp);

//MEMORY
void			*mycalloc(void **ptr_addr, size_t size);
void			*ft_strdup(char *src, char **dst);
void			free_tab(char **tab, size_t size);
void			free_struc(t_exec *struc);

//EXIT
int				iperror(const char *msg, int ret);
void			*pperror(const char *msg, void *ret);
int				close_all(t_exec *struc, unsigned int ret);
int				exit_all(t_exec *struc, unsigned int child, unsigned int ret);

//PRINT
void			fprint(const char *str, int fd);
int				fexprint(char *str, int fd, int ret);

#endif