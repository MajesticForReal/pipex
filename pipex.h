/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:08:05 by anrechai          #+#    #+#             */
/*   Updated: 2022/06/19 03:05:26 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		open_infile;
	int		open_outfile;
	char	**cmd_1;
	char	**cmd_2;
	char	**path;
}	t_pipex;

void	get_cmd(t_pipex *pipex, char **argv);
void	close_fd(int *pipefd, int outfile, int infile);
void	free_str(char **s);
void	dup_andclose(int fd_close2, int old_fd,
			int fd_close, int second_old_fd);
void	ft_clean(t_pipex *pipex);
void	ft_child_process(pid_t child, t_pipex *pipex, int *pipefd);
void	ft_child_process2(pid_t child, t_pipex *pipex, int *pipefd);
void	ft_error(t_pipex *pipex, int *pipefd);

int		ft_search_path(char **env);
int		ft_strlen(char *str);
int		ft_fork(char **cmd, char **envp);
int		ft_pipex(t_pipex *pipex, int status);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	**get_path(char **envp);
char	**ft_split(char const *s, char c);

char	*ft_strcat_path(char *dest, char *src);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);

t_pipex	*ft_open_and_init(char **argv, t_pipex *pipex, char **envp);

#endif
