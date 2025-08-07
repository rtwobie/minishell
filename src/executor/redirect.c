/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:00:47 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/06 18:25:39 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "parser.h"

static int	_open_redirect_in(t_redirection_node *redir_data)
{
	int	fd_in;

	if (redir_data->type != TOKEN_REDIRECT_IN
		&& redir_data->type != TOKEN_HERE_DOC)
		return (EXIT_SUCCESS);
	fd_in = open(redir_data->filename, O_RDONLY);
	if (fd_in == -1)
	{
		perror(redir_data->filename);
		return (EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		perror("dup2 in failed");
		return (EXIT_FAILURE);
	}
	close(fd_in);
	return (EXIT_SUCCESS);
}

static int	_set_input(t_list *redir, int input_fd)
{
	t_list	*current;

	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 in failed");
			return (EXIT_FAILURE);
		}
	}
	if (redir)
	{
		current = redir;
		while (current)
		{
			if (_open_redirect_in((t_redirection_node *)current->content))
				return (EXIT_FAILURE);
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}

static int	_open_redirect_out(t_redirection_node *redir_data)
{
	int	fd;

	if (redir_data->type == TOKEN_REDIRECT_OUT)
		fd = open(redir_data->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redir_data->type == TOKEN_REDIRECT_OUT_APPEND)
		fd = open(redir_data->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		return (EXIT_SUCCESS);
	if (fd == -1)
	{
		perror(redir_data->filename);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("dup2 out failed");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	_set_output(t_list *redir, int output_fd)
{
	t_list	*current;

	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 out failed");
			return (EXIT_FAILURE);
		}
	}
	if (redir)
	{
		current = redir;
		while (current)
		{
			if (_open_redirect_out((t_redirection_node *)current->content))
				return (EXIT_FAILURE);
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}

int	redirect_io(t_command_node *cmd, int input_fd, int output_fd)
{
	if (_set_input(cmd->redir, input_fd))
	{
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
		return (EXIT_FAILURE);
	}
	if (_set_output(cmd->redir, output_fd))
	{
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
		return (EXIT_FAILURE);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
	return (EXIT_SUCCESS);
}
