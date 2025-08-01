/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:31:43 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/01 20:48:04 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				return (EXIT_FAILURE);
			free(current->value);
			current->value = new_value;
		}
		else if (current->type == TOKEN_DOUBLE_QUOTES)
		{
			new_value = ft_strtrim(current->value, "\"");
			if (!new_value)
				return (EXIT_FAILURE);
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
				return (ERR_SYNTAX);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static int	_expand(t_token **tokens)
{
	t_token *current;
	t_token *prev;

	current = *tokens;
	prev = current;
	while (current)
	{
		// EXPANSION CODE HERE
		if (envvar(&current) == EXIT_FAILURE)
		{
			if (!*current->value)
			{
				prev->next = current->next; // not ideal
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

// TODO:	get the variable after $
//			best approach might be to read str and write new one at the same time
//			so first read str for $
//			then read again and write
//			when $ found then save getenv(variable) into string
//			write expandion into the new string
//			repeat until end of string

int	expander(t_token **tokens)
{
	if (_reedit(tokens))
		return (EXIT_FAILURE);
	if (_expand(tokens))
		return (EXIT_FAILURE);
	if (_condense_redirection(tokens))
		return (ERR_SYNTAX);
	// expand variables
	// condense TOKEN_SINGLE_QUOTES and TOKEN_DOUBLE_QUOTES to TOKEN_LITERAL
	return (EXIT_SUCCESS);
}
