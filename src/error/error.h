/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:53:50 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/31 19:02:55 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// ***** CUSTOM ERROR CODES ***** //

# define ERR_SYNTAX -1
# define ERR_TOOMANY_ARGS -2
# define ERR_CMD_NOTFOUND -3

// ****************************** //

void	print_error(int err);
void	print_err(int err, char *location);

#endif // !ERROR_H


