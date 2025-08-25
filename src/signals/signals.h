/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:19:23 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 13:17:29 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <unistd.h>

unsigned char	get_exit_status(pid_t pid);
void			set_interactive_mode(void);
void			set_noninteractive_mode(void);
void			set_ignore_mode(void);
void			set_noninteractive_hdoc_mode(void);

#endif // !SIGNALS_H
