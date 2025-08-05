/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:15:42 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/04 21:57:29 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../error/error.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "libft.h"
#include "tokenizer_internal.h"
#include "tokenizer.h"
#include "error.h"

static char	*_skip_whitespace(char *str)
{
	while(*str)
	{
		if (!ft_isspace(*str))
			break ;
		++str;
	}
	return (str);
}

enum e_state _check_state(char c)
{
	enum e_state state;

	state = 0;
	if (ft_isspace(c))
		state = WHITESPACE;
	else if (c == '\'')
		state = IN_SINGLE_QUOTES;
	else if (c == '\"')
		state = IN_DOUBLE_QUOTES;
	else if (c == '|' || c == '>' || c == '<')
		state = IN_OPERATOR;
	else if (c == '\0')
		state = END;
	else if (ft_isword(c))
		state = WORD;
	return (state);
}


static char	*_get_word_tok(char *idx, t_token **tokens)
{
	size_t	i;

	i = 0;
	while (idx[i] && _check_state(idx[i]) == WORD)
		++i;
	save_token(idx, i, tokens);
	return (&idx[i]);
}

static int	_get_single_quote_tok(char **idx, t_token **tokens)
{
	char *idx_ptr;
	size_t	i;

	i = 0;
	idx_ptr = *idx;
	++idx_ptr;
	while (idx_ptr[i] && _check_state(idx_ptr[i]) != IN_SINGLE_QUOTES)
		++i;
	if (*idx_ptr == '\"')
		save_token("\0", 1, tokens);
	else if (idx_ptr[i] != '\0')
		save_token(*idx, i + 2, tokens);
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
		save_token("\0", 1, tokens);
	else if (idx_ptr[i] != '\0')
		save_token(*idx, i + 2, tokens);
	else
		return (ERR_SYNTAX);
	*idx = &idx_ptr[++i];
	return (EXIT_SUCCESS);
}

static char	*_get_pipe_operator_tok(char *idx, t_token **tokens)
{
	save_token(idx, 1, tokens);
	return(++idx);
}

static char	*_get_input_operator_tok(char *idx, t_token **tokens)
{

	if (*(idx + 1) == '<')
	{
		save_token(idx, 2, tokens);
		idx += 2;
	}
	else
	{
		save_token(idx, 1, tokens);
		idx += 1;
	}
	return(idx);
}

static char	*_get_output_operator_tok(char *idx, t_token **tokens)
{
	if (*(idx + 1) == '>')
	{
		save_token(idx, 2, tokens);
		idx += 2;
	}
	else
	{
		save_token(idx, 1, tokens);
		idx += 1;
	}
	return(idx);
}

static char	*_get_operator_tok(char *idx, t_token **tokens)
{
	if (*idx == '|')
		return (_get_pipe_operator_tok(idx, tokens));
	if (*idx == '<')
		return (_get_input_operator_tok(idx, tokens));
	if (*idx == '>')
		return (_get_output_operator_tok(idx, tokens));
	return (idx);
}

int	lexer(char *user_input, t_token **tokens)
{
	enum e_state	current_state;
	char			*idx;
	int				err;

	err = 0;
	idx = user_input;
	while(1)
	{
		current_state = _check_state(*idx);
		if (current_state == WHITESPACE)
			idx = _skip_whitespace(idx);
		else if (current_state == IN_OPERATOR)
			idx = _get_operator_tok(idx, tokens);
		else if (current_state == IN_SINGLE_QUOTES)
			err = _get_single_quote_tok(&idx, tokens);
		else if (current_state == IN_DOUBLE_QUOTES)
			err = _get_double_quote_tok(&idx, tokens);
		else if (current_state == WORD)
			idx = _get_word_tok(idx, tokens);
		else if (current_state == END)
			break ;
		if (err)
			return (print_err(err, "lexer"), err);
	}
	return (EXIT_SUCCESS);
}
