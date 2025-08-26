/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:33:35 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/26 16:51:29 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "parser.h"

// ast.c
char			**_arglist_to_strarr(t_list **arg_list);
t_redir_node	*_create_redirection_node(t_token *token);
t_ast_node		*_create_command_node(char **args, t_list **redirects);
t_pipe_node		*_init_pipe_data(t_ast_node *left_node, t_ast_node *right_node);
t_ast_node		*_create_ast_node(t_nodetype type, void *data);

// parser1.c
char			*match(t_token **token_ptr, enum e_token_type expected_token);
int				_free_on_error(t_list **arg_list, t_list **redirects);

#endif // !PARSER_INTERNAL_H
