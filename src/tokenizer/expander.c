/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:31:43 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/19 23:00:40 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "error.h"
#include "libft.h"
#include "run.h"
#include "tokenizer.h"
#include "envvar.h"
#include "../error/error.h"

static int	_is_redirection(enum e_token_type type)
{
	return (
		type == TOKEN_REDIRECT_IN || \
		type == TOKEN_REDIRECT_OUT || \
		type == TOKEN_HERE_DOC || \
		type == TOKEN_REDIRECT_OUT_APPEND
	);
}

static int	_reedit(t_token **tokens)
{
	char	*new_value;
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_SINGLE_QUOTES)
		{
			new_value = ft_strtrim(current->value, "\'");
			if (!new_value)
				return (perror("malloc failed"), EXIT_FAILURE);
			free(current->value);
			current->value = new_value;
		}
		else if (current->type == TOKEN_DOUBLE_QUOTES)
		{
			new_value = ft_strtrim(current->value, "\"");
			if (!new_value)
				return (perror("malloc failed"), EXIT_FAILURE);
			free(current->value);
			current->value = new_value;
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static int	_condense_redirection(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	current = *tokens;
	while (current)
	{
		if (_is_redirection(current->type))
		{
			if (current->next && current->next->type == TOKEN_LITERAL)
			{
				free(current->value);
				current->value = ft_strdup(current->next->value);
				temp = current->next;
				current->next = current->next->next;
				free_token(temp);
			}
			else
				return (print_err(ERR_SYNTAX, current->value), EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static int	_expand(t_token **tokens, unsigned char *exit_status, t_data *data)
{
	t_token	*pos[3];

	pos[1] = *tokens;
	pos[0] = NULL;
	while (pos[1])
	{
		pos[2] = pos[1]->next;
		if (envvar(&pos[1], exit_status, 0, data) == EXIT_FAILURE)
		{
			if (!*pos[1]->value)
			{
				if (free_token(pos[1]), 1 && !pos[0])
					*tokens = pos[2];
				else
					pos[0]->next = pos[2];
				pos[1] = pos[2];
			}
			continue ;
		}
		if (pos[1] && (pos[1]->type == 1 || pos[1]->type == 2))
			pos[1]->type = TOKEN_LITERAL;
		pos[0] = pos[1];
		pos[1] = pos[1]->next;
	}
	return (EXIT_SUCCESS);
}

int	expander(t_token **tokens, unsigned char *exit_status, t_data *data)
{
	if (_reedit(tokens))
		return (EXIT_FAILURE);
	if (_expand(tokens, exit_status, data))
		return (EXIT_FAILURE);
	if (_condense_redirection(tokens))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
