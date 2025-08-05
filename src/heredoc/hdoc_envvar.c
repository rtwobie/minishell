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

static char	*_use_getent(char *idx, size_t i)
{
	char	*join;
	char	*temp;
	char	*substr;

	substr = ft_substr(idx, 0, i);
	temp = ft_substr(idx, (unsigned int)i, ft_strlen(idx));
	join = getenv(substr);
	free(substr);
	if (!join && !temp[0])
		return (perror("ENV VAR not found"), NULL);
	else if (!join && temp)
		return (perror("ENV VAR not found"), temp);
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

static int	_get_env_tok(char **idx)
{
	size_t		i;
	char		*t;
	char		*str;

	i = 0;
	if ((*idx)[1] == '{')
	{
		if (rm_braces(idx, &i) == NULL)
			return (free(*idx), *idx = NULL, EXIT_FAILURE);
		t = _use_getent(*idx, i);
		free(*idx);
	}
	else
	{
		str = (*idx) + 1;
		while (str[++i] && (ft_isalnum(str[i]) || str[i] == '_'))
			;
		t = _use_getent(str, i);
		free(*idx);
	}
	if (!t)
		return (EXIT_FAILURE);
	*idx = t;
	return (EXIT_SUCCESS);
}

static int	_dollars(char *input, unsigned int *skip, unsigned int *i)
{
	*i = 0;
	while (input[*skip + *i] && (input[*skip + *i] != '$'))
		++(*skip);
	while (input[*skip] == 36 && (input[*skip + 1] == 36))
		++(*skip);
	if (input[*skip] == '$' && (input[*skip + 1] == '?'))
		return (perror("$?->FOUND\n"), EXIT_FAILURE);
	while (input[*skip + *i] && (input[*skip + *i] != '$'))
		++(*i);
	if (input[*skip + *i] == '$')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	hdoc_envvar(char **input, unsigned int skip)
{
	unsigned int	i;
	char			*temp;
	char			*new;
	char			*val;
	char			*original_value;

	if (_dollars(*input, &skip, &i))
		return (EXIT_SUCCESS);
	val = ft_substr(*input, skip, ft_strlen(*input));
	if (!ft_strcmp("$", val))
		return (free(val), val = NULL, EXIT_SUCCESS);
	temp = ft_substr(*input, 0, skip + i);
	original_value = *input;
	*input = ft_substr(val, i, ft_strlen(val));
	free(original_value);
	if (free(val), 1 && _get_env_tok(input) == EXIT_FAILURE)
		return (*input = temp, EXIT_FAILURE);
	new = ft_strjoin(temp, *input);
	(free(temp), free(*input));
	*input = new;
	hdoc_envvar(input, skip + i);
	return (EXIT_SUCCESS);
}
