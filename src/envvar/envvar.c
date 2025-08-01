/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:42:12 by fgorlich          #+#    #+#             */
/*   Updated: 2025/08/01 22:39:32 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"
#include "tokenizer.h"
#include "tokenizer_internal.h"
#include <stdlib.h>

char	*_use_getent(char *idx, size_t i)
{
	char	*join;
	char	*temp;
	char	*substr;

	substr = ft_substr(idx, 0, i);
	join = getenv(substr);
	free(substr);
	if (!join)
		return (perror("ENV VAR not found"), NULL);
	temp = ft_substr(idx, (unsigned int)i, ft_strlen(idx));
	idx = ft_strjoin(join, temp);
	free(temp);
	return (idx);
}

char	*rm_braces(char **idx, size_t *j)
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

int	_get_env_tok(char **idx)
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

int	envvar(t_token **tokens)
{
	unsigned int	i;
	char			*temp;
	char			*new;
	char			*val;

	i = 0;
	if ((*tokens)->type != TOKEN_DOUBLE_QUOTES
		&& (*tokens)->type != TOKEN_LITERAL)
		return (EXIT_SUCCESS);
	while ((*tokens)->value[i] && (*tokens)->value[i] != '$')
		++i;
	if ((*tokens)->value[i] == '$')
	{
		val = (*tokens)->value;
		temp = ft_substr((*tokens)->value, 0, i);
		(*tokens)->value = ft_substr(val, i, ft_strlen((*tokens)->value));
		if (free(val), 1 && _get_env_tok(&((*tokens)->value)) == EXIT_FAILURE)
			return (free((*tokens)->value), (*tokens)->value = temp,
				EXIT_FAILURE);
		new = ft_strjoin(temp, (*tokens)->value);
		free(temp);
		free((*tokens)->value);
		(*tokens)->value = new;
	}
	return (EXIT_SUCCESS);
}
