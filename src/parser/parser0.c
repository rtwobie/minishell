/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:01:10 by rtwobie           #+#    #+#             */
/*   Updated: 2025/09/11 16:01:13 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "run.h"
#include "tokenizer.h"
#include "parser_internal.h"
#include "parser.h"

static int	_parse_command_elements(t_token **token_ptr, t_list	**arg_list,
t_list **redirects)
{
	char			*arg;
	t_redir_node	*redir_data;

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
