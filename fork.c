/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:17:29 by anrechai          #+#    #+#             */
/*   Updated: 2022/06/19 03:01:54 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && --n > 0 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		s_len;
	int		i;

	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	i = 0;
	dest = malloc((s_len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat_path(char *dest, char *src)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(src) + 2));
	if (!new_str)
		return (NULL);
	while (dest[i])
	{
		new_str[i] = dest[i];
		i++;
	}
	new_str[i] = '/';
	i++;
	while (src[j])
	{
		new_str[i] = src[j];
		j++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

// int	ft_fork(char **cmd, char **path)
// {
// 	char	*my_cmd;
// 	char	*cmd_tmp;
// 	int		i;

// 	i = 0;
// 	my_cmd = ft_strdup(cmd[0]);
// 	cmd_tmp = NULL;
// 	if (strchr(cmd[0], '/'))
// 		execve(cmd[0], cmd, NULL);
// 	else
// 	{
// 		while (path && path[i])
// 		{
// 			free(cmd[0]);
// 			cmd[0] = NULL;
// 			cmd_tmp = ft_strcat_path(path[i], my_cmd);
// 			cmd[0] = cmd_tmp;
// 			execve(cmd[0], cmd, NULL);
// 			i++;
// 		}
// 	}
// 	write(2, "Command not found\n", 18);
// 	free(my_cmd);
// 	return (1);
// }
