/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:15:42 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/23 19:25:51 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "lexer_utils.h"

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

static void	_print_token(char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (str[i] && i < size + 1)
	{
		(void)write(1, &str[i], 1);
		++i;
	}
	(void)write (1, "\n", 1);
}

static enum e_state _check_state(char c)
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

static char	*_get_word_tok(char *idx)
{
	size_t	i;

	i = 0;
	while (idx[i] && _check_state(idx[i]) == WORD)
		++i;
	_print_token(idx, i - 1);
	return (&idx[i]);
}

static char	*_get_single_quote_tok(char *idx)
{
	bool	is_closing;
	size_t	i;

	i = 0;
	is_closing = false;
	++idx;
	while (idx[i])
	{
		if (_check_state(idx[i]) == IN_SINGLE_QUOTES)
		{
			is_closing = true;
			break ;
		}
		++i;
	}
	if (i == 0)
	{
		printf("CREATING EMPTY STRING\n");
		++i;
	}
	else if (is_closing == true)
		_print_token(idx, i++ - 1);
	else
		printf("NO CLOSING SINGLE QUOTE FOUND!\n");
	return (&idx[i]);
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
static char	*_get_double_quote_tok(char *idx)
{
	size_t	i;

	i = 0;
	++idx;
	while (idx[i])
	{
		if (_check_state(idx[i]) == IN_DOUBLE_QUOTES)
			break ;
		++i;
	}
	if (i == 0)
	{
		printf("CREATING EMPTY STRING\n");
		++i;
	}
	else if (idx[i] != '\0')
		_print_token(idx, i++ - 1);
	else
	{
		printf("NO CLOSING SINGLE QUOTE FOUND!\n");
		return (NULL);
	}
	return (&idx[i]);
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

static char	*_get_pipe_operator_tok(char *idx)
{
	_print_token(idx, 0);
	return(++idx);
}

static char	*_get_input_operator_tok(char *idx)
{

	if (*(idx + 1) == '<')
	{
		_print_token(idx, 1);
		idx += 2;
	}
	else
	{
		_print_token(idx, 0);
		idx += 1;
	}
	return(idx);
}

static char	*_get_output_operator_tok(char *idx)
{
	if (*(idx + 1) == '>')
	{
		_print_token(idx, 1);
		idx += 2;
	}
	else
	{
		_print_token(idx, 0);
		idx += 1;
	}
	return(idx);
}

static char	*_get_operator_tok(char *idx)
{
	if (*idx == '|')
		return (_get_pipe_operator_tok(idx));
	if (*idx == '<')
		return (_get_input_operator_tok(idx));
	if (*idx == '>')
		return (_get_output_operator_tok(idx));
	return (idx);
}

int	lexer(char *user_input)
{
	enum e_state	current_state;
	char			*idx;

	current_state = START;
	idx = user_input;
	while(1)
	{
		current_state = _check_state(*idx);
		if (current_state == WHITESPACE)
			idx = _skip_whitespace(idx);
		else if (current_state == IN_OPERATOR)
			idx = _get_operator_tok(idx);
		else if (current_state == IN_SINGLE_QUOTES)
			idx = _get_single_quote_tok(idx);
		else if (current_state == IN_DOUBLE_QUOTES)
			idx = _get_double_quote_tok(idx);
		else if (current_state == WORD)
			idx = _get_word_tok(idx);
		else if (current_state == END)
			break ;
		if (!idx)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// 'slim shady'
