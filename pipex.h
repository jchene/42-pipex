/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:16 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 00:21:46 by jchene           ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define RESET		"\e[0m"

# define READ		0
# define WRITE		1
# define INFILE 	0
# define OUTFILE	1
# define INPUT		0
# define OUTPUT		1
# define CHILD1		0
# define CHILD2		1

typedef struct s_exec1
{
	int		std_fds[2];
	int		pipe_ends[2];
	int		fds[2];
	pid_t	id[2];
	char	*cmds[2];
	char	**splits[2];
	char	*paths[2];
}				t_exec1;

typedef struct s_data
{
	pid_t	*ids;
	int		*(pipes[2]);
	int		files_fds[2];
}				t_data;

typedef struct s_exec
{
	int		in_fds[2];
	int		out_fds[2];
	char	*path;
	char	**args;
}				t_exec;

//LIB

unsigned int	strl(const char *str);
unsigned int	is_charset(const char *charset, char c);
void			ft_strcpyl(char *src, char *dst, unsigned int length);
unsigned int	basic_cmp(const char *str1, char *str2);

//STRING

unsigned int	get_nword(const char *delims, char *str);
char			**split(char *str, const char *delims);

//INIT

int				init_data(t_data *data, int argc);
int				init_exec(t_exec *exec, char **argv, char **envp, int i);

//PARSING

void			pre_init(t_exec1 *struc, char **argv);
int				parse_args(t_exec1 *struc, char **argv, char **envp);

//PATH

char			*get_env(const char *key, char **envp);
int				get_args(t_exec *exec, char **argv, int i);
int				get_path(char **struc_path, char *cmd, char **envp);

//MEMORY

void			*nul(void **ptr_addr, size_t size);
void			*ft_strdup(char *src, char **dst);
void			free_tab(char **tab, size_t size);
void			free_struc(t_exec1 *struc);

//EXIT
int				iperror(const char *msg, int ret);
void			*pperror(const char *msg, void *ret);
int				close_all(t_exec1 *struc, unsigned int ret);
int				exit_all(t_exec1 *struc, unsigned int ret);

//PRINT

void			fprint(const char *str, int fd);
int				fexprint(char *str, int fd, int ret);

#endif