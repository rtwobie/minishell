/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:43:24 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/26 16:51:13 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// NOTE: Forward declaration to avoid circular includes
typedef struct s_data	t_data;

enum e_token_type
{
	TOKEN_LITERAL,
	TOKEN_SINGLE_QUOTES,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HERE_DOC,
	TOKEN_REDIRECT_OUT_APPEND,
	TOKEN_COMBINE,
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}	t_token;

int		lexer(char *user_input, t_token **tokens, unsigned char *exit_status);
int		expander(t_token **tokens, unsigned char *exit_status, t_data *data);
int		_is_redirection(enum e_token_type type);

#endif // !TOKENIZER_H
