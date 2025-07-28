/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:15:25 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/23 16:07:01 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "debug.h"
#include "tokenizer.h"
#include "parser.h"

/** Converts the enum to its string literal. (for debugging)
 *
 *	@param type: 	The enum type.
 *
 *	@returns:		The name of the enum as string.
 */
char	*token_type_to_string(enum e_token_type type)
{
	if (type == TOKEN_LITERAL)
		return ("TOKEN_LITERAL");
	else if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	else if (type == TOKEN_HERE_DOC)
		return ("TOKEN_HERE_DOC");
	else if (type == TOKEN_REDIRECT_OUT_APPEND)
		return ("TOKEN_REDIRECT_OUT_APPEND");
	else if (type == TOKEN_ENVIRONMENT_VARIABLES)
		return ("TOKEN_ENVIRONMENT_VARIABLES");
	else if (type == TOKEN_EXIT_STATUS)
		return ("TOKEN_EXIT_STATUS");
	else if (type == TOKEN_SINGLE_QUOTES)
		return ("TOKEN_SINGLE_QUOTES");
	else if (type == TOKEN_DOUBLE_QUOTES)
		return ("TOKEN_DOUBLE_QUOTES");
	return (NULL);
}

char	*output_type_to_string(enum e_output type)
{
	if (type == STD_OUT)
		return ("STDOUT");
	else if (type == PIPE_OUT)
		return ("PIPE");
	else if (type == FILE_OUT)
		return ("FILE");
	else if (type == FILE_APPEND_OUT)
		return ("FILE_APPEND");
	return (NULL);
}

void	print_token(t_token *token)
{
	printf("%s%s\n%s", YELLOW, token->value, END);
	printf("%s%s\n%s", CYAN, token_type_to_string(token->type), END);
	printf("\n");
}

void	print_all_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		print_token(current);
		current = current->next;
	}
}
