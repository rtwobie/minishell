/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:21:12 by fgroo             #+#    #+#             */
/*   Updated: 2025/08/18 20:12:04 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "run.h"
#include "builtin.h"
#include <asm-generic/errno-base.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

static char	*ft_getenv(char **envp, const char *name)
{
	size_t	name_len;
	size_t	i;

	if (!envp || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

int	is_builtin(char *program)
{
	if (!ft_strcmp(program, "echo") || !ft_strcmp(program, "cd")
		|| !ft_strcmp(program, "pwd") || !ft_strcmp(program, "env")
		|| !ft_strcmp(program, "exit"))
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

int	cd(char **av, t_data *data, ssize_t i)
{
	if (av[0][0] == 'e' && data->envp[++i])
		return (ft_putendl_fd(data->envp[i], STDOUT_FILENO)
			, cd(av, data, i), EXIT_SUCCESS);
	if (av[0][0] == 'p')
		return (ft_putstr_fd(ft_getenv(data->envp, "PWD"), STDOUT_FILENO)
			, write(1, "\n", 1), EXIT_SUCCESS);
	if (av[0][0] == 'c' && av[1] && av[2])
		return (print_err(ERR_ONLY_ONE_ARG, "cd"), EXIT_FAILURE);
	if (av[0][0] == 'c' && !av[1] && chdir(getenv("HOME")) != 0)
		perror("getcwd in home");
	if (av[0][0] == 'c' && av[1] && chdir(av[1]) != 0)
		return (errno = ENOENT, print_err(ENOENT, "cd"), EXIT_FAILURE);
	if (av[0][0] == 'c' && check_entries(data))
		perror("lol");
	return (EXIT_SUCCESS);
}
