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
#include "envvar.h"

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

static int	dollars(t_token **tokens, unsigned int *skip,
	unsigned int *i, unsigned char *exit_status)
{
	const int numerical_value = *exit_status;
	const char *extracted_str = ft_itoa(numerical_value);
	char	*pos[3];

	*i = 0;
	if ((*tokens)->type != TOKEN_DOUBLE_QUOTES
		&& (*tokens)->type != TOKEN_LITERAL)
		return (EXIT_FAILURE);
	while ((*tokens)->value[*skip + *i] && (*tokens)->value[*skip + *i] != '$')
		++(*skip);
	while ((*tokens)->value[*skip] == 36 && (*tokens)->value[*skip + 1] == 36)
		++(*skip);
	if ((*tokens)->value[*skip] == '$' && (*tokens)->value[*skip + 1] == '?')
	{
		pos[0] = ft_strjoin(extracted_str,(*tokens)->value + *skip + 2);
		pos[1] = ft_substr((*tokens)->value, 0, *skip);
		pos[2] = ft_strjoin(pos[1], pos[0]);
		(free((*tokens)->value), free(pos[0]), free(pos[1]), (*tokens)->value = NULL);
		(*tokens)->value = pos[2];
	}
	while ((*tokens)->value[*skip + *i] && (*tokens)->value[*skip + *i] != '$')
		++(*i);
	if ((*tokens)->value[*skip + *i] == '$')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	envvar(t_token **tokens, unsigned char *exit_status, unsigned int skip)
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
	if (free(val), 1 && _get_env_tok(&((*tokens)->value)) == EXIT_FAILURE)
		return ((*tokens)->value = temp, EXIT_FAILURE);
	new = ft_strjoin(temp, (*tokens)->value);
	(free(temp), free((*tokens)->value));
	(*tokens)->value = new;
	envvar(tokens, exit_status, skip + i);
	return (EXIT_SUCCESS);
}
