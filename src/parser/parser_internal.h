/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:33:35 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/20 18:07:56 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "parser.h"

//ast.c
t_ast_node	*_create_ast_node(t_nodetype type, void *data);


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
