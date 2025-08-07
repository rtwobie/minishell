/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:21:12 by fgroo             #+#    #+#             */
/*   Updated: 2025/08/08 00:10:16 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "builtin.h"
#include <asm-generic/errno-base.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

int	is_builtin(char *program)
{
	if (!ft_strcmp(program, "echo") || !ft_strcmp(program, "cd")
		|| !ft_strcmp(program, "pwd") || !ft_strcmp(program, "env"))
		return (1);
	return (0);
}

int	echo(char *argv[])
{
	size_t	i;
	bool	newline;

	if (!argv || !argv[1])
		return (ft_putstr_fd("\n", STDOUT_FILENO), EXIT_SUCCESS);
	i = 1;
	newline = true;
	if (!ft_strcmp("-n", argv[1]))
	{
		newline = false;
		++i;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		++i;
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_FAILURE);
}

int	cd(char **av, char **envp, ssize_t i)
{
	char	cwd[1024];

	if (av[0][0] == 'e' && envp[++i] && ft_putendl_fd(envp[i], STDOUT_FILENO))
		return (cd(av, envp, i), EXIT_SUCCESS);
	if (av[0][0] == 'p' && ft_putstr_fd(getenv("PWD"), STDOUT_FILENO))
		return (write(1, "\n", 1), EXIT_SUCCESS);
	if (av[0][0] == 'c' && (av[1] == NULL || av[2] != NULL))
		return (print_err(ERR_ONLY_ONE_ARG, "cd"), EXIT_FAILURE);
	if (av[0][0] == 'c' && chdir(av[1]) != 0)
		return (errno = ENOENT, print_err(ENOENT, "cd"), EXIT_FAILURE);
	if (av[0][0] == 'c' && getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	return (EXIT_SUCCESS);
}
