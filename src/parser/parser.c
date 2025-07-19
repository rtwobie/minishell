/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:41:08 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/18 19:55:51 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "tokenizer.h"
#include "parser_internal.h"
#include "parser.h"

static int	_is_operator(enum e_token_type type)
{
	return (
		type == TOKEN_PIPE || \
		type == TOKEN_REDIRECT_IN || \
		type == TOKEN_REDIRECT_OUT || \
		type == TOKEN_HERE_DOC || \
		type == TOKEN_REDIRECT_OUT_APPEND
	);
}

static int	_count_args(t_token *tokens)
{
	int	size;

	size = 0;
	while (tokens && !_is_operator(tokens->type))
	{
		++size;
		tokens = tokens->next;
	}
	return (size);
}

// static char	**_init_args(t_token **tokens, size_t size)
// {
// 	char	**args;
// 	t_token *current;
// 	size_t	i;
//
// 	args = ft_calloc(size + 1, sizeof(*args));
// 	if (!args)
// 		return (NULL);
// 	i = 0;
// 	current = *tokens;
// 	while (current && i < size)
// 	{
// 		args[i] = ft_strdup(current->value);
// 		if (!args[i])
// 			free_args(args);
// 		++i;
// 		current = current->next;
// 	}
// 	*tokens = current;
// 	args[i] = NULL;
// 	return (args);
// }















// static t_ast_node	*_parse_pipeline(t_token **token_ptr)
// {
// 	t_ast_node	*
//
// 	return (node);
// }


int	parser(t_token *tokens, t_ast_node	*ast)
{
	if (!tokens)
		return (EXIT_SUCCESS);
	// ast = _parse_pipeline(&tokens);
	_is_operator(TOKEN_PIPE);
	_count_args(tokens);
	(void)ast;
	return (EXIT_SUCCESS);
}
