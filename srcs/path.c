/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:07:11 by jchene            #+#    #+#             */
/*   Updated: 2022/05/09 18:54:13 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_env(const char *key, char **envp)
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

int	get_path(char **struc_path, char *cmd, char **envp)
{
	char			**dirs;
	char			*tmp;
	unsigned int	i;

	dirs = split(&(get_env("PATH", envp)[ft_strlen("PATH=")]), ":");
	i = 0;
	while (dirs[i])
	{
		if (!mycalloc((void **)&(tmp), sizeof(char) * (ft_strlen(dirs[i]) + ft_strlen(cmd) + 2)))
			return (-1);
		ft_strcpyl(dirs[i], tmp, ft_strlen(dirs[i]));
		ft_strcpyl("/", &(tmp[ft_strlen(tmp)]), 1);
		ft_strcpyl(cmd, &(tmp[ft_strlen(tmp)]), ft_strlen(cmd));
		free(dirs[i]);
		dirs[i] = tmp;
		if (!access(dirs[i], X_OK))
			break ;
		i++;
	}
	if (!ft_strdup(dirs[i], struc_path))
		return (-1);
	free_tab(dirs, get_nword(":", &(get_env("PATH", envp)[5])) + 1);
	return (0);
}
