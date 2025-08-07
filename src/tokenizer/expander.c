/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:31:43 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/06 22:48:11 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "error.h"
#include "libft.h"
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
	t_token *temp;

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

static int	_expand(t_token **tokens, unsigned char *exit_status)
{
	t_token 		*current;
	t_token 		*prev;

	current = *tokens;
	prev = current;
	while (current)
	{
		if (envvar(&current, exit_status, 0) == EXIT_FAILURE)
		{
			if (!*current->value)
			{
				prev->next = current->next;
				free_token(current);
				current = prev->next;
			}
			continue ;
		}
		if (current->type == TOKEN_SINGLE_QUOTES || \
			current->type == TOKEN_DOUBLE_QUOTES)
				current->type = TOKEN_LITERAL;
		prev = current;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	expander(t_token **tokens, unsigned char *exit_status)
{
	if (_reedit(tokens))
		return (EXIT_FAILURE);
	if (_expand(tokens, exit_status))
		return (EXIT_FAILURE);
	if (_condense_redirection(tokens))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
