/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:16 by jchene            #+#    #+#             */
/*   Updated: 2022/05/02 14:41:24 by jchene           ###   ########.fr       */
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

//LIB
unsigned int	ft_strlen(const char *str);
unsigned int	is_charset(const char *charset, char c);
void			ft_strcpyl(char *src, char *dst, unsigned int length);
unsigned int	get_nb_words(const char *delims, char *str);
char			**split(char *str, const char *delims);

//MEMORY
void			*ft_calloc(size_t size);
void			free_split(char **tab, unsigned int nword);

//EXIT
int				experror(const char *msg);

//PRINT
void			fprint(const char *str, int fd);
int				fexprint(char *str, int fd, int ret);

#endif