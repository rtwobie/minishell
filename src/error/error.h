/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:53:50 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/04 19:57:47 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// ***** CUSTOM ERROR CODES ***** //

# define ERR_SYNTAX -1
# define ERR_TOOMANY_ARGS -2

// ****************************** //

void	print_error(int err);

#endif // !ERROR_H


