/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:16 by jchene            #+#    #+#             */
/*   Updated: 2022/04/25 17:34:47 by jchene           ###   ########.fr       */
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

# define NB_ARG	-1

typedef struct s_pipex
{
	char	*infile_name;
	char	*outfile_name;
	char	*cmd1;
	char	*cmd2;
}				t_pipex;

unsigned int	ft_strlen(const char *str);
void			ft_putstr(const char *str);

#endif