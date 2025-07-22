/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:41:08 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/19 19:29:12 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

static size_t	_count_args(t_token *tokens)
{
	size_t	size;

	size = 0;
	while (tokens && !_is_operator(tokens->type))
	{
		++size;
		tokens = tokens->next;
	}
	return (size);
}

static char	**_init_args(t_token **tokens, size_t size)
{
	char	**args;
	t_token *current;
	size_t	i;

	args = ft_calloc(size + 1, sizeof(*args));
	if (!args)
		return (NULL);
	i = 0;
	current = *tokens;
	while (current && i < size)
	{
		args[i] = ft_strdup(current->value);
		if (!args[i])
			free_args(args);
		++i;
		current = current->next;
	}
	*tokens = current;
	args[i] = NULL;
	return (args);
}






char	*match(t_token **token_ptr, enum e_token_type expected_token)
{
	t_token	*current_token;

	current_token = *token_ptr;
	if (current_token->type != expected_token)
		return (NULL);
	else
		*token_ptr = current_token->next;
	return (current_token->value);
}

static t_ast_node	*_parse_command(t_token **token_ptr)
{
	t_ast_node		*node;
	t_command_node	*cmd_node;

	if (!(*token_ptr) || (*token_ptr)->type != TOKEN_LITERAL)
		return (NULL);
	cmd_node = ft_calloc(1, sizeof(*cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->program_argv = _init_args(token_ptr, _count_args(*token_ptr));
	if (!cmd_node->program_argv)
	{
		free(cmd_node);
		return (NULL);
	}
	node = ft_calloc(1, sizeof(*node));
	if (!node)
	{
		free_args(cmd_node->program_argv);
		free(cmd_node);
		return (NULL);
	}

	// TODO: REDIRECTIONS

	node->type = NODE_TYPE_COMMAND;
	node->data.command_node = cmd_node;
	return (node);
}

// static t_ast_node	*_create_pipe_node(t_ast_node *left_node, t_ast_node *right_node)
// {
// 	t_ast_node	*pipe_node;
//
// 	pipe_node = ft_calloc(1, sizeof(*pipe_node));
// 	if (!pipe_node)
// 		return (NULL);
// 	return (pipe_node);
// }

static t_ast_node	*_parse_pipeline(t_token **token_ptr)
{
	// t_ast_node	*pipe_node;
	t_ast_node	*left_node;
	t_ast_node	*right_node;
	t_pipe_node	*pipe_data;

	(void)pipe_data;
	left_node = _parse_command(token_ptr);
	if (!left_node)
		return (NULL);
	while (*token_ptr && (*token_ptr)->type == TOKEN_PIPE)
	{
		if (!match(token_ptr, TOKEN_PIPE))
		{
			//cleanup_nodes()
			return (NULL);
		}
		right_node = _parse_pipeline(token_ptr);
		if (!right_node)
		{
			//cleanup_nodes()
			return (NULL);
		}
		// pipe_node = _create_pipe_node(left_node, right_node);
	}
	return (left_node);
}

int	parser(t_token *tokens, t_ast_node	**ast)
{
	if (!tokens)
		return (EXIT_SUCCESS);
	*ast = _parse_pipeline(&tokens);
	if (!*ast)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
