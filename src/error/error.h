/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:53:50 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/07 16:58:42 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// ***** CUSTOM ERROR CODES ***** //

# define ERR_SYNTAX -1
# define ERR_TOOMANY_ARGS -2
# define ERR_CMD_NOTFOUND -3
# define ERR_ONLY_ONE_ARG -4

// ****************************** //

void	print_error(int err);
void	print_err(int err, char *location);

#endif // !ERROR_H
