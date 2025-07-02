/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:43:24 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/29 15:46:03 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "structs.h"

int	lexer(char *user_input, t_token **tokens);
int	expander(t_token **tokens);
int	parser(t_token *tokens);

#endif // !TOKENIZER_H
