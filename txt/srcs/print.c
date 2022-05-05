/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:42:42 by jchene            #+#    #+#             */
/*   Updated: 2022/04/30 17:43:07 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	fprint(const char *str, int fd)
{
	if (fd == 2)
		write(2, "\e[31m", 5);
	write(fd, str, ft_strlen((str)));
	if (fd == 2)
		write(2, "\e[0m", 4);
}

int	fexprint(char *str, int fd, int ret)
{
	fprint(str, fd);
	return (ret);
}
