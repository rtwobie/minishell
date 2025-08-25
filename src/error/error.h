/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:53:50 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 18:21:05 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// ***** CUSTOM ERROR CODES ***** //

# define ERR_SYNTAX -1
# define ERR_TOOMANY_ARGS -2
# define ERR_CMD_NOTFOUND -3
# define ERR_INVAL_NODE -4
# define ERR_UNEXPECTED_TOK -5
# define ERR_NUM_ARG_REQUIRED -6

// ****************************** //

void	print_hdoc_warning(char *eof);
void	print_err_unexpected_tok(char *value);
void	print_err(int err, char *location);

#endif // !ERROR_H
