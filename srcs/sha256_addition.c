/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_addition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:11:34 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:57:32 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern uint32_t	g_h0;
extern uint32_t	g_h1;
extern uint32_t	g_h2;
extern uint32_t	g_h3;
extern uint32_t	g_h4;
extern uint32_t	g_h5;
extern uint32_t	g_h6;
extern uint32_t	g_h7;

void			init(void)
{
	g_h0 = 0x6A09E667;
	g_h1 = 0xBB67AE85;
	g_h2 = 0x3C6EF372;
	g_h3 = 0xA54FF53A;
	g_h4 = 0x510E527F;
	g_h5 = 0x9B05688C;
	g_h6 = 0x1F83D9AB;
	g_h7 = 0x5BE0CD19;
}

void			change_len(t_string *str)
{
	size_t		size;
	uint32_t	val_tmp;

	size = str->size / 4;
	val_tmp = ((uint32_t*)(str->str))[size - 2];
	((uint32_t*)(str->str))[size - 2] =\
				reverse_4_bytes(((uint32_t*)(str->str))[size - 1]);
	((uint32_t*)(str->str))[size - 1] = reverse_4_bytes(val_tmp);
}

static uint32_t	*get_block(uint8_t *ptr)
{
	uint32_t	*block;
	size_t		i;

	if (!(block = (uint32_t*)ft_memalloc(sizeof(uint32_t) * 16)))
		return (NULL);
	i = 0;
	while (i < sizeof(uint32_t) * 16)
	{
		block[i / 4] = reverse_4_bytes(*(uint32_t*)&(ptr[i]));
		i += 4;
	}
	return (block);
}

uint32_t		**get_blocks(t_string *str)
{
	uint32_t	**blocks;
	size_t		i;

	blocks = (uint32_t**)ft_memalloc(sizeof(uint32_t*) *\
			(str->size / sizeof(uint32_t) / 16 + 1));
	i = 0;
	while (i < str->size / sizeof(uint32_t) / 16)
	{
		blocks[i] = get_block((uint8_t*)&(str->str[i * 16 * 4]));
		++i;
	}
	return (blocks);
}
