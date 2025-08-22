/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:07:09 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 14:15:57 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "error.h"
#include "heredoc.h"
#include "libft.h"
#include "signals.h"
#include "tokenizer.h"

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

static int	_hdoc_readline(int fd, char *delimiter)
{
	char			*input;
	unsigned char	exit_status;

	exit_status = 0;
	set_noninteractive_hdoc_mode();
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (close(fd), print_hdoc_warning(delimiter), EXIT_SUCCESS);
		if (!ft_strcmp(input, delimiter))
		{
			free(input);
			break ;
		}
		hdoc_envvar(&input, 0, &exit_status);
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	return (exit_status);
}

static char	*_hdoc(char *delimiter, int count, unsigned char *exit_status)
{
	int		fd;
	char	*tmpfile;
	pid_t	pid;

	tmpfile = _generate_name(count);
	if (!tmpfile)
		return (NULL);
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (perror("creating heredoc file"), NULL);
	pid = fork();
	if (pid == -1)
	{
		perror("fork in hdoc failed");
		return (unlink(tmpfile), free(tmpfile), close(fd), NULL);
	}
	else if (pid == 0)
		exit(_hdoc_readline(fd, delimiter));
	set_ignore_mode();
	*exit_status = get_exit_status(pid);
	set_interactive_mode();
	if (*exit_status)
		return (close(fd), free(tmpfile), NULL);
	return (close(fd), tmpfile);
}

int	heredoc(t_token **tokens, unsigned char *exit_status)
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
		hdoc = _hdoc(current->value, count, exit_status);
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
	t_token	*current;

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
