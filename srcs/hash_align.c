/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_align.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:09:56 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:41:21 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static bool		add_byte(t_string *str, int8_t byte)
{
	if (!(str->str = ft_realloc_modf(str->str, str->size + 2, str->size)))
		return (false);
	(str->str)[str->size] = byte;
	++(str->size);
	return (true);
}

static void		add_original_len(t_string *str, size_t len)
{
	add_byte(str, (len & 0xff));
	add_byte(str, (len & 0xff00) >> (BYTE_SIZE));
	add_byte(str, (len & 0xff0000) >> (BYTE_SIZE * 2));
	add_byte(str, (len & 0xff000000) >> (BYTE_SIZE * 3));
	add_byte(str, (len & 0xff00000000) >> (BYTE_SIZE * 4));
	add_byte(str, (len & 0xff0000000000) >> (BYTE_SIZE * 5));
	add_byte(str, (len & 0xff000000000000) >> (BYTE_SIZE * 6));
	add_byte(str, (len & 0xff00000000000000) >> (BYTE_SIZE * 7));
}

uint16_t		reverse_2_bytes(uint16_t b)
{
	return (b << 8 | b >> 8);
}

uint32_t		reverse_4_bytes(uint32_t b)
{
	return (b >> 24 | ((b >> 8) & 0xff00) | ((b << 8) & 0xff0000) | b << 24);
}

bool			align_str(t_string *str)
{
	size_t		len;

	len = str->size * BYTE_SIZE;
	if (!(add_byte(str, (int8_t)0x80)))
		return (false);
	while ((str->size * BYTE_SIZE) % 512 != 448)
		if (!(add_byte(str, (int8_t)0x00)))
			return (false);
	add_original_len(str, len);
	return (true);
}
