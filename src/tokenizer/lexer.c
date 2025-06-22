/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:15:42 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/21 01:56:10 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "lexer.h"

int	ft_isoperator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

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
	while (str[i] && i < size)
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
	else if (c == '\0')
		state = END;
	else if (ft_isoperator(c))
		state = OPERATOR;
	else if (ft_isalnum(c))
		state = WORD;

	return (state);
}

static enum e_state	_update_state(enum e_state *state, enum e_state new_state)
{
	enum e_state	prev_state;

	prev_state = *state;
	*state = new_state;
	return (prev_state);
}

void	lexer(char *user_input)
{
	enum e_state	state;
	enum e_state	prev_state;
	char			*idx;
	size_t			i;

	state = START;
	i = 0;
	idx = _skip_whitespace(user_input);
	while(1)
	{
		prev_state = _update_state(&state, _check_state(user_input[i]));
		if (prev_state == START)
			;
		else if (prev_state == WHITESPACE)
			idx = &user_input[i];
		else if (prev_state == OPERATOR)
		{
			if (user_input[i] == '>' && user_input[i + 1] == '>')
				;
			else
			{
				_print_token(idx, i - (size_t)(idx - user_input));
				idx = &user_input[i];
			}
		}
		else if (prev_state == WORD && prev_state != state)
		{
			_print_token(idx, i - (size_t)(idx - user_input));
			idx = &user_input[i];
		}
		if (!user_input[i])
			break ;
		++i;
	}
}
