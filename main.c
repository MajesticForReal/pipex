/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:06:25 by anrechai          #+#    #+#             */
/*   Updated: 2022/06/19 03:05:30 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(pid_t child, t_pipex *pipex, int *pipefd)
{
	if (child == -1)
	{
		perror("fork");
		ft_error(pipex, pipefd);
	}
	if (child == 0)
	{
		dup_andclose(pipex->fd_out, pipex->fd_in, pipefd[0], pipefd[1]);
		ft_fork(pipex->cmd_1, pipex->path);
		if (pipex->fd_out != -1)
			close(pipex->fd_out);
		ft_clean(pipex);
		exit(EXIT_FAILURE);
	}
}

void	ft_child_process2(pid_t child2, t_pipex *pipex, int *pipefd)
{
	if (child2 == -1)
	{
		perror("fork");
		ft_error(pipex, pipefd);
	}
	if (child2 == 0)
	{
		dup_andclose(pipex->fd_in, pipefd[0], pipefd[1], pipex->fd_out);
		ft_fork(pipex->cmd_2, pipex->path);
		if (pipex->fd_in != -1)
			close(pipex->fd_in);
		ft_clean(pipex);
		exit(EXIT_FAILURE);
	}
}

int	ft_fork(char **cmd, char **path)
{
	int		i;
	char	*new_path;
	char	*my_cmd;

	new_path = NULL;
	my_cmd = ft_strdup(cmd[0]);
	i = 0;
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, NULL);
	}
	while (path && path[i])
	{
		free(cmd[0]);
		cmd[0] = NULL;
		new_path = ft_strcat_path(path[i], my_cmd);
		if (new_path == NULL)
			return (0);
		cmd[0] = new_path;
		if (access(new_path, X_OK) == 0)
			execve(new_path, cmd, NULL);
		i++;
	}
 	write(2, "Command not found\n", 18);
	free(my_cmd);
	return (0);
}

int	ft_pipex(t_pipex *pipex, int status)
{
	pid_t	child;
	pid_t	child2;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		ft_error(pipex, pipefd);
	}
	if (pipex->open_infile != -1)
	{
		child = fork();
		ft_child_process(child, pipex, pipefd);
	}
	if (pipex->open_outfile != -1)
	{
		child2 = fork();
		ft_child_process2(child2, pipex, pipefd);
	}
	child = 0;
	child2 = 0;
	close_fd(pipefd, pipex->fd_in, pipex->fd_out);
	waitpid(child, &status, 0);
	waitpid(child2, &status, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		status;

	status = 0;
	if (argc != 5)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (-1);
	}
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (-1);
	ft_open_and_init(argv, pipex, envp);
	get_cmd(pipex, argv);
	ft_pipex(pipex, status);
	ft_clean(pipex);
	return (0);
}
