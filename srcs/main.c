/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:20:10 by jchene            #+#    #+#             */
/*   Updated: 2022/04/25 17:50:39 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	print_exit(int code)
{
	if (code == NB_ARG)
		ft_putstr("Wrong number of arguments\n");
	if (code < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_pipex	args;

	if (argc != 5)
		return (print_exit(NB_ARG));
	if (parse_args(&args) < 0)
		return (0);
	return (0);
}
