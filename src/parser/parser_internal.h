/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:33:35 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/19 17:58:22 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

typedef enum e_nodetype
{
	NODE_TYPE_COMMAND,
	NODE_TYPE_ARGUMENT,
	NODE_TYPE_PIPE,
	NODE_TYPE_REDIRECTION,
}	t_nodetype;

typedef struct s_ast_node			t_ast_node;
typedef struct s_command_node		t_command_node;
typedef struct s_argument_node		t_argument_node;
typedef struct s_argument_segment	t_argument_segment;
typedef struct s_pipe_node			t_pipe_node;
typedef struct s_redirection_node	t_redirection_node;

struct s_command_node
{
	char	**program_argv;
};

struct s_pipe_node
{
	t_ast_node	*left;
	t_ast_node	*right;
};

// struct s_redirection_node
// {
// 	enum e_token_type	type;
// 	char				*file_path;
// };
//
union u_node
{
	struct s_command_node	*command_node;
	struct s_pipe_node		*pipe_node;
};

struct s_ast_node
{
	t_nodetype		type;
	union u_node	data;
};

void	free_args(char **args);
void	free_cmd(void *command_struct);

#endif // !PARSER_INTERNAL_H

// typedef enum e_arg_segment_type
// {
// 	ARG_PART_TEXT,
// 	ARG_PART_VARIABLE,
// }	t_arg_segment_type;
//
// struct s_argument_segment
// {
// 	t_arg_segment_type	type;
// 	char				*value;
// };
//
// struct s_argument_node
// {
// 	t_list	*segments;
// };
//
