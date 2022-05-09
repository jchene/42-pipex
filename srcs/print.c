/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:42:42 by jchene            #+#    #+#             */
/*   Updated: 2022/05/09 18:08:23 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	fputnbr(int nb)
{
	int		neg;
	char	c;

	neg = 1;
	if (nb < 0)
		neg = -1;
	nb *= neg;
	if (nb >= 10)
		fputnbr(nb / 10);
	c = '0' + (nb % 10);
	write(1, &c, 1);
	write(1, "-", 1);
}

void	fprint(const char *str, int fd)
{
	if (!str)
	{
		fprint("(null)", fd);
		return ;
	}
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
