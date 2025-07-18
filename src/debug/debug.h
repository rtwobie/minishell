/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:24:53 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/18 15:50:36 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "parser.h"
# include "structs.h"

char	*token_type_to_string(enum e_token_type type);
void	print_cmd(t_command *cmd);
void	print_token(t_token *token);
void	print_all_tokens(t_token *tokens);

#endif // !DEBUG_H
