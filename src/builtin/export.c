/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:43:05 by fgroo             #+#    #+#             */
/*   Updated: 2025/08/26 16:11:11 by fgroo            ###   ########.fr       */
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

static int	gillette(char **a, char *part[4], size_t *i, size_t l)
{
	if (!(ft_isalpha((*a)[0]) || (*a)[0] == '_') && write(2, "export: »", 9))
		return (write(2, *a, l), write(2, "«: not a valid beginner\n", 26), 1);
	while ((*a)[*i] && (ft_isalnum((*a)[*i]) || (*a)[*i] == '_'))
		++(*i);
	if ((*a)[*i] && (*a)[*i] != '=' && write(2, "export: »", 9))
		return (write(2, *a, l),
			write(2, "«: not a valid identifier\n", 26), 1);
	else if (!(*a)[*i])
		return (EXIT_SUCCESS);
	part[0] = ft_substr(*a, 0, *i + 1);
	if (!part[0])
		return (*i = ULONG_MAX, EXIT_FAILURE);
	part[1] = ft_substr(*a, (unsigned int)*i + 1, l);
	if (!part[1])
		return (free(part[0]), EXIT_FAILURE);
	part[2] = ft_strtrim(part[1], "'");
	if (free(part[1]), 1 && !part[2])
		return (free(part[0]), EXIT_FAILURE);
	part[1] = ft_strtrim(part[2], "\"");
	if (free(part[2]), 1 && !part[1])
		return (free(part[0]), EXIT_FAILURE);
	part[2] = ft_calloc(1, l + 3);
	if (!part[2])
		return (free(part[0]), EXIT_FAILURE);
	return (free(*a), *a = NULL, EXIT_SUCCESS);
}

static int	refactor_arg(char **arg, size_t len, int *exit_status)
{
	size_t	i;
	char	*part[4];

	ft_memset(part, 0, sizeof part);
	i = 0;
	if (gillette(arg, part, &i, len))
		return (*exit_status = 1, EXIT_FAILURE);
	else if (*arg)
		return (EXIT_SUCCESS);
	i = ULONG_MAX;
	part[2][0] = '"';
	while (part[1][++i])
	{
		if (part[1][i] == '"' || part[1][i] == '\'')
			continue ;
		part[2][i + 1] = part[1][i];
	}
	free(part[1]);
	part[2][++i] = '"';
	part[1] = ft_substr(part[2], 0, i + 1);
	part[3] = ft_strjoin(part[0], part[1]);
	return (*arg = part[3], free(part[0]),
		free(part[1]), free(part[2]), EXIT_SUCCESS);
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
		refactor_arg(&tmp[i[2]], ft_strlen(tmp[i[2]]), &(int){0});
		printf("declare -x %s\n", tmp[i[2]]);
		tmp[i[2]][0] = 127;
	}
	free_args(tmp);
}

int	_unset(const char *target, const size_t tlen, t_data *data, int *flag)
{
	size_t	i;
	size_t	j;
	size_t	nb;
	char	**cpy;

	nb = ULONG_MAX;
	i = ULONG_MAX;
	j = ULONG_MAX;
	while (data->envp[++i] && (ft_strncmp(data->envp[i], target, tlen)
			|| (data->envp[i][tlen] != '=' && data->envp[i][tlen] != '\0')))
		;
	if (!data->envp[i])
		return (EXIT_SUCCESS);
	while (data->envp[i + ++j])
		;
	cpy = malloc(sizeof(char *) * (j + i));
	if (!cpy)
		return (EXIT_FAILURE);
	while (++nb < i)
		cpy[nb] = ft_strdup(data->envp[nb]);
	while (data->envp[++i])
		cpy[nb++] = ft_strdup(data->envp[i]);
	cpy[nb] = NULL;
	free_args(data->envp);
	return (data->envp = cpy, *flag = -1, EXIT_SUCCESS);
}

int	_export(char **av, t_data *data, int exit_status)
{
	size_t	i[2];
	int		flag;

	flag = 0;
	i[0] = 0;
	i[1] = 0;
	while (data->envp[i[1]])
		i[1]++;
	if (!av[1])
		return (print_env(data->envp, i[1]), EXIT_SUCCESS);
	while (av[++i[0]])
	{
		if (refactor_arg(&av[i[0]], ft_strlen(av[i[0]]), &exit_status))
			continue ;
		if (delete_entry(av[i[0]], data, &flag))
			return (EXIT_FAILURE);
		if (flag && flag--)
			continue ;
		i[1] = 0;
		while (data->envp[i[1]])
			i[1]++;
		if (add_entry(av[i[0]], data, i[1], 1))
			return (EXIT_FAILURE);
	}
	return (exit_status);
}
