/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:09:32 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:38:38 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t		*md5(t_string *input)
{
	uint8_t		*hash;

	if (!input || !(input->str))
		return (NULL);
	align_str(input);
	hash = calculate_md5(input);
	return (hash);
}
