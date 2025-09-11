/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:42:12 by fgroo          #+#    #+#             */
/*   Updated: 2025/08/01 23:31:31 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "builtin.h"

static char	*_use_getent(char *idx, size_t i, unsigned int *skip, char **envp)
{
	char	*join;
	char	*temp;
	char	*substr;

	substr = ft_substr(idx, 0, i);
	temp = ft_substr(idx, (unsigned int)i, ft_strlen(idx));
	join = ft_getenv(envp, substr);
	free(substr);
	if (!join && !temp[0])
		return (free(temp), NULL);
	else if (!join && temp)
		return (temp);
	else if (!join)
		return (free(temp), NULL);
	*skip += (unsigned int)ft_strlen(join);
	idx = ft_strjoin(join, temp);
	free(temp);
	return (idx);
}

static char	*rm_braces(char **idx, size_t *j)
{
	unsigned int	i;
	char			*temp1;
	char			*temp2;

	i = 0;
	while ((*idx)[i] && (*idx)[i] != '}')
		i++;
	if (!(*idx)[i])
		return (perror("Syntax error in env_tok"), NULL);
	temp1 = ft_substr((*idx), 2, i - 2);
	temp2 = ft_substr((*idx), i + 1, ft_strlen((*idx)) - i);
	free(*idx);
	*idx = ft_strjoin(temp1, temp2);
	*j = i - 2;
	return (free(temp1), free(temp2), *idx);
}

static int	_get_env_tok(char **idx, unsigned int *skip, char **envp)
{
	size_t	i;
	char	*t;
	char	*str;

	i = 0;
	if ((*idx)[1] == '{')
	{
		if (rm_braces(idx, &i) == NULL)
			return (free(*idx), *idx = NULL, EXIT_FAILURE);
		t = _use_getent(*idx, i, skip, envp);
		free(*idx);
	}
	else
	{
		str = (*idx) + 1;
		while (str[++i] && (ft_isalnum(str[i]) || str[i] == '_'))
			;
		t = _use_getent(str, i, skip, envp);
		free(*idx);
	}
	if (!t)
		return (EXIT_FAILURE);
	*idx = t;
	return (EXIT_SUCCESS);
}

static int	_dollars(char **input, unsigned int *skip,
unsigned int *i, unsigned char *exit_status)
{
	const int	numerical_value = *exit_status;
	char		*extr_str;
	char		*pos[3];

	*i = 0;
	while ((*input)[*skip + *i] && (*input)[*skip + *i] != '$')
		++(*skip);
	while ((*input)[*skip] == '$'
		&& ((*input)[*skip + 1] == '$' || ft_isspace((*input)[*skip + 1])))
		++(*skip);
	if ((*input)[*skip] == '$' && (*input)[*skip + 1] == '?')
	{
		extr_str = ft_itoa(numerical_value);
		pos[0] = ft_strjoin(extr_str, (*input) + *skip + 2);
		pos[1] = ft_substr((*input), 0, *skip);
		(free((*input)), pos[2] = ft_strjoin(pos[1], pos[0]));
		(free(*pos), free(pos[1]), free(extr_str), (*input) = pos[2]);
	}
	while ((*input)[*skip + *i] && (*input)[*skip + *i] != '$')
		++(*i);
	if ((*input)[*skip + *i] == '$')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	hdoc_envvar(char **input, unsigned int skip, unsigned char *exit_status,
char **envp)
{
	unsigned int	i;
	char			*temp;
	char			*new;
	char			*val;
	char			*original_value;

	if (_dollars(input, &skip, &i, exit_status))
		return (EXIT_SUCCESS);
	val = ft_substr(*input, skip, ft_strlen(*input));
	if (!ft_strcmp("$", val))
		return (free(val), val = NULL, EXIT_SUCCESS);
	temp = ft_substr(*input, 0, skip + i);
	original_value = *input;
	*input = ft_substr(val, i, ft_strlen(val));
	free(original_value);
	if (free(val), 1 && _get_env_tok(input, &skip, envp) == EXIT_FAILURE)
		return (*input = temp, EXIT_FAILURE);
	new = ft_strjoin(temp, *input);
	(free(temp), free(*input));
	*input = new;
	hdoc_envvar(input, skip + i, exit_status, envp);
	return (EXIT_SUCCESS);
}
