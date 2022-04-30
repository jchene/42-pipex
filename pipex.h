/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:16 by jchene            #+#    #+#             */
/*   Updated: 2022/04/30 18:15:45 by jchene           ###   ########.fr       */
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
# include <sys/types.h>
# include <fcntl.h>

# define READ		0
# define WRITE		1
# define INFILE 	0
# define OUTFILE	1

unsigned int	ft_strlen(const char *str);
int				experror(const char *msg);
char			**split(char *str, const char *delims);

void			fprint(const char *str, int fd);
int				fexprint(char *str, int fd, int ret);

#endif