/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:43:24 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/04 17:27:27 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft.h"
# include "structs.h"

int	lexer(char *user_input, t_token **tokens);
int	expander(t_token **tokens);
int	parser(t_list **cmd_list, t_token *tokens);
int	executor(t_list **cmd_list);

#endif // !TOKENIZER_H
