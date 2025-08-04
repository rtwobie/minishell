/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:07:09 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/04 18:59:59 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "libft.h"
#include "tokenizer.h"
#include "heredoc.h"

// TODO: SIGNAL HANDLING
// TODO: env expansion in heredoc

static char	*_generate_name(int count)
{
	char		*acount;
	char		*tmpfile;

	acount = ft_itoa(count);
	if (!acount)
		return (perror("malloc"), NULL);
	tmpfile = ft_strjoin(HDOCDIR, acount);
	if (!tmpfile)
	{
		free(acount);
		return (perror("malloc"), NULL);
	}
	free(acount);
	return (tmpfile);
}

static char	*_hdoc(char *delimiter, int count)
{
	int		fd;
	char	*input;
	char	*tmpfile;

	tmpfile = _generate_name(count);
	if (!tmpfile)
		return (NULL);
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (perror("heredoc"), NULL);
	while (1)
	{
		input = readline("> ");
		if (!ft_strcmp(input, delimiter))
		{
			free(input);
			break ;
		}
		// input = envvar();
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	return (tmpfile);
}

int	heredoc(t_token **tokens)
{
	int		count;
	char	*hdoc;
	t_token	*current;

	count = 0;
	current = *tokens;
	while (current)
	{
		if (current->type != TOKEN_HERE_DOC)
		{
			current = current->next;
			continue ;
		}
		hdoc = _hdoc(current->value, count);
		if (!hdoc)
			return (EXIT_FAILURE);
		free(current->value);
		current->value = hdoc;
		++count;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	cleanup_hdoc(t_token **tokens)
{
	t_token *current;

	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_HERE_DOC)
			if (unlink(current->value))
				return (perror("unlink"), EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
