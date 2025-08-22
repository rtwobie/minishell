/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:15:42 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/22 19:23:55 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "tokenizer_internal.h"
#include "tokenizer.h"
#include "error.h"

static char	*_get_word_tok(char *idx, t_token **tokens)
{
	size_t	i;

	i = 0;
	while (idx[i] && _check_state(idx[i]) == WORD)
		++i;
	save_token(tokens, idx, i, TOKEN_LITERAL);
	return (&idx[i]);
}

static int	_get_single_quote_tok(char **idx, t_token **tokens)
{
	char	*idx_ptr;
	size_t	i;

	i = 0;
	idx_ptr = *idx;
	++idx_ptr;
	while (idx_ptr[i] && _check_state(idx_ptr[i]) != IN_SINGLE_QUOTES)
		++i;
	if (*idx_ptr == '\'')
		save_token(tokens, "\0", 1, TOKEN_SINGLE_QUOTES);
	else if (idx_ptr[i] != '\0')
		save_token(tokens, *idx, i + 2, TOKEN_SINGLE_QUOTES);
	else
		return (ERR_SYNTAX);
	*idx = &idx_ptr[++i];
	return (EXIT_SUCCESS);
}

static int	_get_double_quote_tok(char **idx, t_token **tokens)
{
	char	*idx_ptr;
	size_t	i;

	i = 0;
	idx_ptr = *idx;
	++idx_ptr;
	while (idx_ptr[i] && _check_state(idx_ptr[i]) != IN_DOUBLE_QUOTES)
		++i;
	if (*idx_ptr == '\"')
		save_token(tokens, "\0", 1, TOKEN_DOUBLE_QUOTES);
	else if (idx_ptr[i] != '\0')
		save_token(tokens, *idx, i + 2, TOKEN_DOUBLE_QUOTES);
	else
		return (ERR_SYNTAX);
	*idx = &idx_ptr[++i];
	return (EXIT_SUCCESS);
}

static int	_get_word_and_quotes_tok(char **idx, t_token **tokens,
enum e_state current_state)
{
	int	err;

	err = 0;
	while (1)
	{
		if (current_state == IN_SINGLE_QUOTES)
			err = _get_single_quote_tok(idx, tokens);
		else if (current_state == IN_DOUBLE_QUOTES)
			err = _get_double_quote_tok(idx, tokens);
		else if (current_state == WORD)
			*idx = _get_word_tok(*idx, tokens);
		if (err)
			return (err);
		current_state = _check_state(**idx);
		if (current_state == WORD
			|| current_state == IN_SINGLE_QUOTES
			|| current_state == IN_DOUBLE_QUOTES)
			save_token(tokens, "\0", 1, TOKEN_COMBINE);
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

int	lexer(char *user_input, t_token **tokens, unsigned char *exit_status)
{
	enum e_state	current_state;
	char			*idx;
	int				err;

	err = 0;
	idx = user_input;
	while (1)
	{
		current_state = _check_state(*idx);
		if (current_state == WHITESPACE)
			idx = _skip_whitespace(idx);
		else if (current_state == IN_OPERATOR)
			idx = _get_operator_tok(idx, tokens);
		else if (current_state == WORD
			|| current_state == IN_SINGLE_QUOTES
			|| current_state == IN_DOUBLE_QUOTES)
			err = _get_word_and_quotes_tok(&idx, tokens, current_state);
		else if (current_state == END)
			break ;
		if (err)
			return (print_err(err, "lexer"), *exit_status = 2, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
