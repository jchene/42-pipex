/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:26:14 by jchene            #+#    #+#             */
/*   Updated: 2022/04/25 17:14:58 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

unsigned int	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(const char *str)
{
	write(1, str, ft_strlen((str)));
}
