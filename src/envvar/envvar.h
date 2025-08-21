/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:39:38 by fgroo             #+#    #+#             */
/*   Updated: 2025/08/20 18:11:53 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVVAR_H
# define ENVVAR_H

# include "tokenizer.h"

typedef struct s_data	t_data;

int	envvar(t_token **tokens, unsigned char *exit_status,
		unsigned int skip, t_data *data);

#endif
