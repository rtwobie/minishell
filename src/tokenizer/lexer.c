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
	while (str[i] && i <= size)
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
	else if (c == '\0')
		state = END;
	else if (ft_isword(c))
		state = WORD;
	return (state);
}

static void _update_state(enum e_state state[3], char *input, size_t idx, bool lock_state)
{
	state[0] = state[1];
	if (lock_state == false)
		state[1] = _check_state(input[idx]);
	state[2] = _check_state(input[idx + 1]);
}

void	lexer(char *user_input)
{
	bool			lock_state;
	enum e_state	state[3];
	char			*idx;
	size_t			i;

	lock_state = false;
	state[1] = START;
	i = 0;
	idx = _skip_whitespace(user_input);
	while(1)
	{
		_update_state(state, user_input, i, lock_state);
		if (state[0] == START)
			continue ;
		if (state[1] != state[2])
		{
			if (state[1] == WHITESPACE)
				idx = &user_input[i + 1];
			else if (state[2] == IN_SINGLE_QUOTES)
			{
				if (!lock_state)
					lock_state = true;
				else
					lock_state = false;
			}
			else if (state[1] == WORD)
			{
				_print_token(idx, i - (size_t)(idx - user_input));
				idx = &user_input[i];
			}
		}
		if (!user_input[i])
			break ;
		++i;
	}
}

// 'slim shady'
