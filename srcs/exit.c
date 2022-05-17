/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:14:18 by jchene            #+#    #+#             */
/*   Updated: 2022/05/17 02:26:43 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	iperror(const char *msg, int ret)
{
	perror(msg);
	return (ret);
}

void	*pperror(const char *msg, void *ret)
{
	perror(msg);
	return (ret);
}
