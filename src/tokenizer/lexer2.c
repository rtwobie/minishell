/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:32:16 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 19:25:20 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "tokenizer_internal.h"

static char	*_get_pipe_operator_tok(char *idx, t_token **tokens)
{
	save_token(tokens, idx, 1, TOKEN_PIPE);
	return (++idx);
}

static char	*_get_input_operator_tok(char *idx, t_token **tokens)
{
	if (*(idx + 1) == '<')
	{
		save_token(tokens, idx, 2, TOKEN_HERE_DOC);
		idx += 2;
	}
	else
	{
		save_token(tokens, idx, 1, TOKEN_REDIRECT_IN);
		idx += 1;
	}
	return (idx);
}

static char	*_get_output_operator_tok(char *idx, t_token **tokens)
{
	if (*(idx + 1) == '>')
	{
		save_token(tokens, idx, 2, TOKEN_REDIRECT_OUT_APPEND);
		idx += 2;
	}
	else
	{
		save_token(tokens, idx, 1, TOKEN_REDIRECT_OUT);
		idx += 1;
	}
	return (idx);
}

char	*_get_operator_tok(char *idx, t_token **tokens)
{
	if (*idx == '|')
		return (_get_pipe_operator_tok(idx, tokens));
	else if (*idx == '<')
		return (_get_input_operator_tok(idx, tokens));
	else if (*idx == '>')
		return (_get_output_operator_tok(idx, tokens));
	return (idx);
}
