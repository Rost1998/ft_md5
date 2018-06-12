/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:11:42 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 22:06:55 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

#define A (av[0])
#define B (av[1])
#define C (av[2])
#define D (av[3])
#define E (av[4])
#define F (av[5])
#define G (av[6])
#define H (av[7])
#define E0 (av[8])
#define E1 (av[9])
#define MA (av[10])
#define CH (av[11])
#define T1 (av[12])
#define T2 (av[13])

uint32_t	g_h0;
uint32_t	g_h1;
uint32_t	g_h2;
uint32_t	g_h3;
uint32_t	g_h4;
uint32_t	g_h5;
uint32_t	g_h6;
uint32_t	g_h7;

uint32_t	g_k[64] =
{
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
	0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
	0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
	0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
	0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
	0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
	0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
	0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
	0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
	0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
	0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
	0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
	0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
};

static bool		gen_addit_48_words(uint32_t **block)
{
	size_t		i;
	uint32_t	s0;
	uint32_t	s1;

	if (!(*block = ft_realloc_modf(*block, sizeof(uint32_t) * (16 + 48),\
					sizeof(uint32_t) * 16)))
		return (false);
	i = 16;
	while (i < 64)
	{
		s0 = rotr_right((*block)[i - 15], 7) ^ rotr_right((*block)[i - 15], 18)
						^ ((*block)[i - 15] >> 3);
		s1 = rotr_right((*block)[i - 2], 17) ^ rotr_right((*block)[i - 2], 19)
						^ ((*block)[i - 2] >> 10);
		(*block)[i] = (*block)[i - 16] + s0 + (*block)[i - 7] + s1;
		++i;
	}
	return (true);
}

static void		init_aux_vars(uint32_t *av)
{
	av[0] = g_h0;
	av[1] = g_h1;
	av[2] = g_h2;
	av[3] = g_h3;
	av[4] = g_h4;
	av[5] = g_h5;
	av[6] = g_h6;
	av[7] = g_h7;
}

static void		calculate(uint32_t **block, uint32_t *av, size_t i)
{
	E0 = rotr_right(A, 2) ^ rotr_right(A, 13) ^ rotr_right(A, 22);
	MA = (A & B) ^ (A & C) ^ (B & C);
	T2 = E0 + MA;
	E1 = rotr_right(E, 6) ^ rotr_right(E, 11) ^ rotr_right(E, 25);
	CH = (E & F) ^ (~E & G);
	T1 = H + E1 + CH + g_k[i] + (*block)[i];
	H = G;
	G = F;
	F = E;
	E = D + T1;
	D = C;
	C = B;
	B = A;
	A = T1 + T2;
}

static bool		stage(uint32_t **block)
{
	uint32_t	av[14];
	size_t		i;

	gen_addit_48_words(block);
	init_aux_vars(av);
	i = 0;
	while (i < 64)
	{
		calculate(block, av, i);
		++i;
	}
	g_h0 += av[0];
	g_h1 += av[1];
	g_h2 += av[2];
	g_h3 += av[3];
	g_h4 += av[4];
	g_h5 += av[5];
	g_h6 += av[6];
	g_h7 += av[7];
	return (true);
}

uint8_t			*calculate_sha256(uint32_t **blocks)
{
	size_t		i;
	uint8_t		*hash;

	init();
	i = 0;
	while (blocks[i])
		stage(&blocks[i++]);
	hash = (uint8_t*)ft_memalloc(sizeof(uint8_t) * 32);
	((uint32_t*)hash)[0] = reverse_4_bytes(g_h0);
	((uint32_t*)hash)[1] = reverse_4_bytes(g_h1);
	((uint32_t*)hash)[2] = reverse_4_bytes(g_h2);
	((uint32_t*)hash)[3] = reverse_4_bytes(g_h3);
	((uint32_t*)hash)[4] = reverse_4_bytes(g_h4);
	((uint32_t*)hash)[5] = reverse_4_bytes(g_h5);
	((uint32_t*)hash)[6] = reverse_4_bytes(g_h6);
	((uint32_t*)hash)[7] = reverse_4_bytes(g_h7);
	return (hash);
}
