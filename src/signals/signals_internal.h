/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:17:15 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 13:18:09 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_INTERNAL_H
# define SIGNALS_INTERNAL_H

# include <unistd.h>

void	_reset_prompt(int sig);
void	_newline(int sig);

#endif // !SIGNALS_INTERNAL_H
