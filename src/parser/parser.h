/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:37:31 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/20 18:07:18 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "libft.h"
# include "tokenizer.h"

typedef struct s_ast_node			t_ast_node;
typedef struct s_command_node		t_command_node;
typedef struct s_pipe_node			t_pipe_node;
typedef struct s_redirection_node	t_redirection_node;

enum e_output
{
	STD_OUT,
	PIPE_OUT,
	FILE_OUT,
	FILE_APPEND_OUT,
};

typedef enum e_nodetype
{
	NODE_TYPE_COMMAND,
	NODE_TYPE_PIPE,
}	t_nodetype;

struct s_command_node
{
	char	**argv;
	t_list	*redir;
};

struct s_redirection_node
{
	enum e_token_type	type;
	char				*filename;
};

struct s_pipe_node
{
	t_ast_node	*left;
	t_ast_node	*right;
};

union u_node
{
	struct s_command_node		*command;
	struct s_pipe_node			*pipe;
};

struct s_ast_node
{
	t_nodetype		type;
	union u_node	data;
};

//parser.c
int		parser(t_token *tokens, t_ast_node	**ast);

#endif // !PARSER_H
