/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eviroment.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:33:13 by mmagrin           #+#    #+#             */
/*   Updated: 2025/05/26 18:25:24 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

#endif
