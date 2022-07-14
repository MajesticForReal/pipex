/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 21:31:44 by anrechai          #+#    #+#             */
/*   Updated: 2022/06/19 03:05:14 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(int *pipefd, int outfile, int infile)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	if (infile != -1)
		close(infile);
	if (outfile != -1)
		close(outfile);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	ft_error(t_pipex *pipex, int *pipefd)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	ft_clean(pipex);
	pipex = NULL;
	exit(EXIT_FAILURE);
}

t_pipex	*ft_open_and_init(char **argv, t_pipex *pipex, char **envp)
{
	int		infile;
	int		outfile;
	int		open_infile;
	int		open_outfile;

	open_infile = 1;
	open_outfile = 1;
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
	{
		perror(argv[1]);
		open_infile = -1;
	}
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror(argv[4]);
		if (infile != -1)
			close(infile);
		free(pipex);
		exit(EXIT_FAILURE);
		open_outfile = -1;
	}
	pipex->open_outfile = open_outfile;
	pipex->open_infile = open_infile;
	pipex->fd_in = infile;
	pipex->fd_out = outfile;
	pipex->path = get_path(envp);
	return (pipex);
}
