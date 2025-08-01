/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:07:09 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/30 17:42:58 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "libft.h"
#include "tokenizer.h"

// TODO: SIGNAL HANDLING
int	heredoc(char *delimiter)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!ft_strcmp(input, delimiter))
		{
			free(input);
			break ;
		}
		free(input);
	}
	printf("DELIMITER DETECTED!\n");
	return (EXIT_SUCCESS);
}

int	heredoc_test(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_HERE_DOC)
			heredoc(current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
