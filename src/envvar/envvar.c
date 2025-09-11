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

#include "builtin.h"
#include "libft.h"
#include "run.h"
#include "envvar.h"

static char	*_use_getent(t_data *data, char *idx, size_t i, unsigned int *skip)
{
	char	*join;
	char	*temp;
	char	*substr;

	substr = ft_substr(idx, 0, i);
	temp = ft_substr(idx, (unsigned int)i, ft_strlen(idx));
	join = ft_getenv(data->envp, substr);
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

static int	_get_env_tok(t_data *data, char **idx, unsigned int *skip)
{
	size_t	i;
	char	*t;
	char	*str;

	i = 0;
	if ((*idx)[1] == '{')
	{
		if (rm_braces(idx, &i) == NULL)
			return (free(*idx), *idx = NULL, EXIT_FAILURE);
		t = _use_getent(data, *idx, i, skip);
		free(*idx);
	}
	else
	{
		str = (*idx) + 1;
		while (str[++i] && (ft_isalnum(str[i]) || str[i] == '_'))
			;
		t = _use_getent(data, str, i, skip);
		free(*idx);
	}
	if (!t)
		return (EXIT_FAILURE);
	*idx = t;
	return (EXIT_SUCCESS);
}

static int	dollars(t_token **tok, unsigned int *skip,
	unsigned int *i, unsigned char *exit_status)
{
	const int	numerical_value = *exit_status;
	char		*extr_str;
	char		*pos[3];

	*i = 0;
	if ((*tok)->type != TOKEN_DOUBLE_QUOTES && (*tok)->type != TOKEN_LITERAL)
		return (EXIT_FAILURE);
	while ((*tok)->value[*skip + *i] && (*tok)->value[*skip + *i] != '$')
		++(*skip);
	while ((*tok)->value[*skip] == 36 && ((*tok)->value[*skip + 1] == 36
			|| ft_isspace((*tok)->value[*skip + 1])))
		++(*skip);
	if ((*tok)->value[*skip] == '$' && (*tok)->value[*skip + 1] == '?')
	{
		extr_str = ft_itoa(numerical_value);
		pos[0] = ft_strjoin(extr_str, (*tok)->value + *skip + 2);
		pos[1] = ft_substr((*tok)->value, 0, *skip);
		(free((*tok)->value), pos[2] = ft_strjoin(pos[1], pos[0]));
		(free(*pos), free(pos[1]), free(extr_str), (*tok)->value = pos[2]);
	}
	while ((*tok)->value[*skip + *i] && (*tok)->value[*skip + *i] != '$')
		++(*i);
	if ((*tok)->value[*skip + *i] == '$')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	envvar(t_token **tokens, unsigned char *exit_status,
		unsigned int skip, t_data *data)
{
	unsigned int	i;
	char			*temp;
	char			*new;
	char			*val;
	char			*original_value;

	if (dollars(tokens, &skip, &i, exit_status))
		return (EXIT_SUCCESS);
	val = ft_substr((*tokens)->value, skip, ft_strlen((*tokens)->value));
	if (!ft_strcmp("$", val))
		return (free(val), val = NULL, EXIT_SUCCESS);
	temp = ft_substr((*tokens)->value, 0, skip + i);
	original_value = (*tokens)->value;
	(*tokens)->value = ft_substr(val, i, ft_strlen(val));
	free(original_value);
	if (free(val), 1 && _get_env_tok(data, &((*tokens)->value),
			&skip) == EXIT_FAILURE)
		return ((*tokens)->value = temp, EXIT_FAILURE);
	new = ft_strjoin(temp, (*tokens)->value);
	(free(temp), free((*tokens)->value));
	(*tokens)->value = new;
	return (envvar(tokens, exit_status, skip + i, data));
}
