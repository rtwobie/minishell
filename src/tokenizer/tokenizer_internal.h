/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:02:36 by rtwobie           #+#    #+#             */
/*   Updated: 2025/09/11 16:02:37 by rtwobie          ###   ########.fr       */
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

// expander1.c
int				_is_redirection(enum e_token_type type);
int				_remove_and_combine(t_token **token_ptr);

// lexer1.c
int				ft_isoperator(char c);
int				ft_isword(unsigned char c);
char			*_skip_whitespace(char *str);
enum e_state	_check_state(char c);

// lexer2.c
char			*_get_operator_tok(char *idx, t_token **tokens);

// token.c
int				save_token(t_token **list, char *str, size_t size, \
enum e_token_type type);

// token_list.c
t_token			*new_token(enum e_token_type type, char *value);
t_token			*get_last_token(t_token *lst);
void			add_token(t_token **lst, t_token *token);

#endif // !TOKENIZER_INTERNAL_H
