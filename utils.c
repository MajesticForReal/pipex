/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:48:43 by anrechai          #+#    #+#             */
/*   Updated: 2022/06/15 21:19:08 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_str(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	get_cmd(t_pipex *pipex, char **argv)
{
	pipex->cmd_1 = ft_split(argv[2], ' ');
	pipex->cmd_2 = ft_split(argv[3], ' ');
}

void	dup_andclose(int fd_close2, int old_fd, int fd_close, int second_old_fd)
{
	if (fd_close2 != -1)
		close(fd_close2);
	if (fd_close != -1)
		close(fd_close);
	dup2(old_fd, 0);
	if (old_fd != -1)
		close(old_fd);
	dup2(second_old_fd, 1);
	if (second_old_fd != -1)
		close(second_old_fd);
}

void	ft_clean(t_pipex *pipex)
{
	free_str(pipex->cmd_1);
	free_str(pipex->cmd_2);
	free_str(pipex->path);
	free(pipex);
}
