/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:06:25 by anrechai          #+#    #+#             */
/*   Updated: 2022/06/01 20:34:53 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;

	// if (argc != 5)
	// {
		// write(2, "invalid number of arguments\n", 28);
		// return (0);
	// }
	ft_check_env(envp, argv);
	printf("OKOK\n");
	return (0);
}

void	ft_check_env(char **envp, char **argv)
{
	int		i;
	char	**cmd;

	cmd = malloc(sizeof(char *) * 3);
	cmd[0] = "cat";
	cmd[1] = argv[1];
	cmd[2] = NULL;
	printf("IN CHECK\n");
	i = 0;
	if (!envp[i])
	{
		printf("OK PAS DE ENV\n");
		if (access(argv[2], X_OK) == 0)
		{
			printf("ACESSOK\n");
			execve(argv[2], cmd, envp);

		}
		else
			perror("command not found ");
	}
	free(cmd[0]);
	free(cmd[1]);
	free(cmd[2]);
	free(cmd);
	return ;
}
