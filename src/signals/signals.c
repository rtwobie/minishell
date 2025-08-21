/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:14:56 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/21 15:22:48 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

static void	_reset_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

static void	_newline(int sig)
{
	(void)sig;
	printf("\n");
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
