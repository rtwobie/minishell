/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:39:38 by fgorlich          #+#    #+#             */
/*   Updated: 2025/08/04 21:37:25 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVVAR_H
# define ENVVAR_H

# include "tokenizer.h"

int	envvar(t_token **tokens, unsigned char *exit_status, unsigned int skip);

#endif
