/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:43:05 by fgroo             #+#    #+#             */
/*   Updated: 2025/08/21 00:56:06 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "error.h"
#include "libft.h"
#include "run.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int refactor_arg(char *arg, size_t len);
static void print_env(char **env, size_t len);

int	_export(char **av, t_data *data)
{
	size_t	i;

	i = 0;
	if (!av[1])
		return (print_env(data->envp), EXIT_SUCCESS);
	while (av[++i])
	{
		if (refactor_arg(av[i], ft_strlen(av[i])))
			return (EXIT_FAILURE);
		if (add_entry(av[i], data, ft_strlen(av[i]), 1))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	print_env(char **env, size_t len)
{
	size_t i[4];

	i[0] = len;
	while (i[0]-- > 0)
	{
		i[2] = 0;
		i[1] = 0;
		while (++i[1] < len)
		{
			i[3] = 0;
			while (env[i[1]][i[3]] && env[i[2]][i[3]]
					&& env[i[1]][i[3]] == env[i[2]][i[3]])
				i[3]++;
			if (env[i[1]][i[3]] < env[i[2]][i[3]])
				i[2] = i[1];
		}
		printf("declare -x %s\n", env[i[2]]);
		env[i[2]] = "~";
	}
}

static int refactor_arg(char *arg, size_t len)
{
	char	new[(size_t){sizeof(len)}];

	new[0] = 90;
	(void)new;
	(void)arg;
	return (EXIT_SUCCESS);
}
