/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:01:53 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/31 13:04:08 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INTERNAL_H
# define TOKENIZER_INTERNAL_H

# include <stddef.h>
# include "tokenizer.h"

enum e_state
{
	START,
	WHITESPACE,
	IN_SINGLE_QUOTES,
	IN_DOUBLE_QUOTES,
	IN_OPERATOR,
	IN_PIPE_OPERATOR,
	IN_OUTPUT_OPERATOR,
	IN_INPUT_OPERATOR,
	WORD,
	END,
};

// lexer.c
enum e_state	_check_state(char c);

// lexer_utils.c
int		ft_isoperator(char c);
int		ft_isword(unsigned char c);

// token.c
int		save_token(char *value, size_t size, t_token **tokens);

// token_list.c
t_token	*new_token(enum e_token_type type, char *value);
t_token	*get_last_token(t_token *lst);
void	add_token(t_token **lst, t_token *token);

#endif // !TOKENIZER_INTERNAL_H
