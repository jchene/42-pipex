/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:33:03 by jchene            #+#    #+#             */
/*   Updated: 2022/05/02 19:33:09 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	parse_args(char **argv, int fds[2])
{
	fds[INFILE] = open(argv[1], O_RDONLY);
	if (fds[INFILE] == 0)
		return (-1);
	fds[OUTFILE] = open(argv[1], O_WRONLY | O_CREAT);
	if (fds[OUTFILE] == 0)
		return (-1);
	return (0);
}
