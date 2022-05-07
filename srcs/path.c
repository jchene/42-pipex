/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:07:11 by jchene            #+#    #+#             */
/*   Updated: 2022/05/07 15:31:22 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_env_value(const char *key, char **envp)
{
	unsigned int	i;

	i = 0;
	while (envp[i])
	{
		if (!basic_cmp(key, envp[i]))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

int	get_path(char *struc_path, char *cmd, char **envp)
{
	char			**dirs;
	char			*tmp;
	unsigned int	i;

	(void)struc_path;
	dirs = split(&(get_env_value("PATH", envp)[5]), ":");
	i = 0;
	while (dirs[i])
	{
		tmp = dirs[i];
		if (!mycalloc((void **)&(dirs[i]), ft_strlen(tmp) + ft_strlen(cmd) + 2))
			return (-1);
		ft_strcpyl(tmp, &(dirs[i][0]), ft_strlen(tmp));
		ft_strcpyl("/", &(dirs[i][ft_strlen(dirs[i])]), 1);
		ft_strcpyl(cmd, &(dirs[i][ft_strlen(dirs[i])]), ft_strlen(cmd));
		free(tmp);
		printf("dir[%d]: %s\n", i, dirs[i]);
		i++;
	}
	return (0);
}
