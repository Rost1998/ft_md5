/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:11:26 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 22:12:33 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t			*sha256(t_string *input)
{
	uint8_t		*hash;
	uint32_t	**blocks;

	align_str(input);
	change_len(input);
	if (!(blocks = get_blocks(input)))
		return (NULL);
	hash = calculate_sha256(blocks);
	return (hash);
}
