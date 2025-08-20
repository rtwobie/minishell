/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:24:53 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/20 18:12:12 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "parser.h"
# include "tokenizer.h"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define END	"\033[0m"

char	*token_type_to_string(enum e_token_type type);
void	print_token(t_token *token);
void	print_all_tokens(t_token *tokens);

//degug_ast.c
void	print_command_node(t_command_node *cmd, int level);
void	print_ast(t_ast_node *node, int level);

#endif // !DEBUG_H
