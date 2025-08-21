/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:43:05 by fgroo             #+#    #+#             */
/*   Updated: 2025/08/21 20:31:51 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "error.h"
#include "libft.h"
#include "parser.h"
#include "run.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int refactor_arg(char *arg, size_t len);
static void print_env(char **env, size_t len);
static int	gilette(char *arg, char	*part[4], size_t *i, size_t len);

int	_export(char **av, t_data *data)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while(data->envp[len])
			len++;
	if (!av[1])
		return (print_env(data->envp, len), EXIT_SUCCESS);
	while (av[++i])
	{
		while(data->envp[len])
			len++;
		if (refactor_arg(av[i], ft_strlen(av[i])))
			return (EXIT_FAILURE);
		if (add_entry(av[i], data, len, 1))
			return (EXIT_FAILURE);
		len = 0;
	}
	return (EXIT_SUCCESS);
}

static void	print_env(char **env, size_t len)
{
	size_t	i[4];
	char	**tmp;

	tmp = cpy_envp(env);
	i[0] = len;
	while (i[0]-- > 0)
	{
		i[2] = 0;
		i[1] = 0;
		while (++i[1] < len)
		{
			i[3] = 0;
			while (tmp[i[1]][i[3]] && tmp[i[2]][i[3]]
					&& tmp[i[1]][i[3]] == tmp[i[2]][i[3]])
				i[3]++;
			if (tmp[i[1]][i[3]] < tmp[i[2]][i[3]])
				i[2] = i[1];
		}
		printf("declare -x %s\n" , tmp[i[2]]);
		tmp[i[2]][0] = 127;
	}
	free_args(tmp);
}
static int refactor_arg(char *arg, size_t len)
{
	size_t	i;
	char	*part[4];

	i = 0;
	if (gilette(arg, part, &i, len))
		return (EXIT_FAILURE);
	else
	 	return (EXIT_SUCCESS);
	i = ULONG_MAX;
	part[2][0] = '"';
	while (part[1][++i])
	{
		if (part[1][i] == '"' || part[1][i] == '\'')
			continue ;
		part[2][i] = part[1][i];
	}
	free(part[1]);
	part[2][i] = '"';
	part[1] = ft_substr(part[2], 0, i);
	part[3] = ft_strjoin(part[0], part[1]);
	return (free(arg), arg = part[3], free(part[1]), free(part[2]), EXIT_SUCCESS);
}

static int	gilette(char *arg, char	*part[4], size_t *i, size_t len)
{
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (EXIT_FAILURE);
	while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
		++*i;
	if (arg[*i] && arg[*i] != '=')
		return (EXIT_FAILURE);
	else
	 	return (EXIT_SUCCESS);
	part[0] = ft_substr(arg, 0, *i);
	if (!part[0])
		return (EXIT_FAILURE);
	part[1] = ft_substr(arg, (unsigned int)*i + 1, len);
	if (!part[1])
		return (free(part[0]), EXIT_FAILURE);
	part[2] = ft_strtrim("'", part[1]);
	if (free(part[1]), 1 && !part[2])
		return (free(part[0]), EXIT_FAILURE);
	part[1] = ft_strtrim("\"", part[2]);
	if (free(part[2]), 1 && !part[1])
		return (free(part[0]), EXIT_FAILURE);
	part[2] = malloc(len + 3);
	if (free(part[1]), 1 && !part[2])
		return (free(part[0]), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
