/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:37:31 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/22 19:49:10 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_token			t_token;
typedef struct s_ast_node		t_ast_node;
typedef struct s_command_node	t_command_node;

enum e_output
{
	STD_OUT,
	PIPE_OUT,
	FILE_OUT,
	FILE_APPEND_OUT,
};

int		parser(t_token *tokens, t_ast_node	**ast);

//cleanup.c
void	free_command_node(t_command_node *node);
void	cleanup_ast(t_ast_node *ast);

#endif // !PARSER_H
