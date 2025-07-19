/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:24:53 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/18 20:01:52 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "tokenizer.h"

char	*token_type_to_string(enum e_token_type type);
// void	print_cmd(t_command *cmd);
void	print_token(t_token *token);
void	print_all_tokens(t_token *tokens);

#endif // !DEBUG_H
