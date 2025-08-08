/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:41:08 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/23 16:47:24 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "tokenizer.h"
#include "parser_internal.h"
#include "parser.h"

static int	_is_redirection(enum e_token_type type)
{
	return (
		type == TOKEN_REDIRECT_IN || \
		type == TOKEN_REDIRECT_OUT || \
		type == TOKEN_HERE_DOC || \
		type == TOKEN_REDIRECT_OUT_APPEND
	);
}

char	*match(t_token **token_ptr, enum e_token_type expected_token)
{
	t_token	*current;

	current = *token_ptr;
	if (current->type != expected_token)
		return (NULL);
	else
		*token_ptr = current->next;
	return (current->value);
}

static int _free_on_error(t_list **arg_list, t_list **redirects)
{
	ft_lstclear(arg_list, free);
	ft_lstclear(redirects, free_redir);
	return (EXIT_FAILURE);
}

static t_redirection_node	*_create_redirection_node(t_token *token)
{
	t_redirection_node	*node;

	if (!_is_redirection(token->type))
		return (NULL);
	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->filename = ft_strdup(token->value);
	if (!node->filename)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

static int	_parse_command_elements(t_token **token_ptr, t_list	**arg_list, t_list **redirects)
{
	char				*arg;
	t_redirection_node	*redir_data;

	while ((*token_ptr) && (*token_ptr)->type != TOKEN_PIPE)
	{
		if ((*token_ptr)->type == TOKEN_LITERAL)
		{
			arg = ft_strdup((*token_ptr)->value);
			if (!arg)
				return (_free_on_error(arg_list, redirects));
			ft_lstadd_back(arg_list, ft_lstnew(arg));
		}
		else if (_is_redirection((*token_ptr)->type))
		{
			redir_data = _create_redirection_node((*token_ptr));
			if (!redir_data)
				return (_free_on_error(arg_list, redirects));
			ft_lstadd_back(redirects, ft_lstnew(redir_data));
		}
		(*token_ptr) = (*token_ptr)->next;
	}
	return (EXIT_SUCCESS);
}

static char **_arglist_to_strarr(t_list **arg_list)
{
	size_t	i;
	size_t	size;
	t_list	*current;
	char	**args;

	current = *arg_list;
	size = (size_t)ft_lstsize(current);
	args = ft_calloc(size + 1, sizeof(*args));
	if (!args)
		return (NULL);
	i = 0;
	while (i < size)
	{
		args[i] = ft_strdup(current->content);
		if (!args[i])
		{
			free_args(args);
			ft_lstclear(arg_list, free);
			return (NULL);
		}
		++i;
		current = current->next;
	}
	ft_lstclear(arg_list, free);
	return (args);
}

static t_ast_node	*_create_command_node(char **args, t_list **redirects)
{
	t_ast_node		*node;
	t_command_node	*cmd_data;

	cmd_data = malloc(sizeof(*cmd_data));
	if (!cmd_data)
		return (NULL);
	node = ft_calloc(1, sizeof(*node));
	if (!node)
	{
		free_args(args);
		ft_lstclear(redirects, free_redir);
		return (NULL);
	}
	cmd_data->program_argv = args;
	cmd_data->redir = *redirects;
	node->data.command = cmd_data;
	node->type = NODE_TYPE_COMMAND;
	return (node);
}

static t_ast_node	*_parse_command(t_token **token_ptr)
{
	t_list	*redirects;
	t_list	*arg_list;
	char	**args;

	if (!(*token_ptr) || ((*token_ptr)->type != TOKEN_LITERAL
		&& !_is_redirection((*token_ptr)->type)))
		return (NULL);
	redirects = NULL;
	arg_list = NULL;
	if (_parse_command_elements(token_ptr, &arg_list, &redirects))
		return (NULL);
	args = _arglist_to_strarr(&arg_list);
	if (!args)
	{
		ft_lstclear(&arg_list, free);
		ft_lstclear(&redirects, free_redir);
		return (NULL);
	}
	return (_create_command_node(args, &redirects));
}

static t_pipe_node	*_init_pipe_data(t_ast_node *left_node,
t_ast_node *right_node)
{
	t_pipe_node	*pipe;

	pipe = ft_calloc(1, sizeof(*pipe));
	if (!pipe)
		return (NULL);
	pipe->left = left_node;
	pipe->right = right_node;
	return (pipe);
}

static t_ast_node	*_parse_pipeline(t_token **token_ptr)
{
	t_ast_node	*left_node;
	t_ast_node	*right_node;
	t_ast_node	*pipe_node;
	t_pipe_node	*pipe_data;

	left_node = _parse_command(token_ptr);
	if (!left_node)
		return (NULL);
	while (*token_ptr && (*token_ptr)->type == TOKEN_PIPE)
	{
		if (!match(token_ptr, TOKEN_PIPE))
			return (cleanup_ast(&left_node), NULL);
		right_node = _parse_command(token_ptr);
		if (!right_node)
			return (cleanup_ast(&left_node), NULL);
		pipe_data = _init_pipe_data(left_node, right_node);
		if (!pipe_data)
			return (cleanup_ast(&left_node), cleanup_ast(&right_node), NULL);
		pipe_node = _create_ast_node(NODE_TYPE_PIPE, pipe_data);
		if (!pipe_node)
			return (cleanup_ast(&left_node), cleanup_ast(&right_node),
				free(pipe_data), NULL);
		left_node = pipe_node;
	}
	return (left_node);
}

int	parser(t_token *tokens, t_ast_node	**ast)
{
	if (!tokens)
		return (EXIT_SUCCESS);
	*ast = _parse_pipeline(&tokens);
	if (!*ast)
		return (perror("parser"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
