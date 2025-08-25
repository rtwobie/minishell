/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:14:56 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 13:19:22 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "signal.h"
#include "signals_internal.h"

unsigned char	get_exit_status(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return ((unsigned char)WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return ((unsigned char)(WTERMSIG(status) + 128));
	return ((unsigned char)status);
}

void	set_interactive_mode(void)
{
	signal(SIGINT, _reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	set_ignore_mode(void)
{
	signal(SIGINT, _newline);
	signal(SIGQUIT, SIG_IGN);
}

void	set_noninteractive_mode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_noninteractive_hdoc_mode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
