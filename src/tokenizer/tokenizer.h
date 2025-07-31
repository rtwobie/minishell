/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:43:24 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/31 13:04:14 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

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
	TOKEN_ENVIRONMENT_VARIABLES,
	TOKEN_EXIT_STATUS,
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}	t_token;

int		lexer(char *user_input, t_token **tokens);
int		expander(t_token **tokens);

// token_list.c
void	free_tokens(t_token **lst);
void	free_token(t_token *token);

#endif // !TOKENIZER_H
