/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:10:05 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:55:24 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <printf.h>
#include "ft_ssl.h"

const int			g_md5_size;
const int			g_size_const_arr = 65;
const int			g_num_of_stages = 4;

unsigned			g_t[g_size_const_arr];

uint32_t			g_a;
uint32_t			g_b;
uint32_t			g_c;
uint32_t			g_d;

/*
** stage 1
*/
t_params			g_params_stage_1[16] =
{
	{ft_f, &g_a, &g_b, &g_c, &g_d, 0, 7, 1},
	{ft_f, &g_d, &g_a, &g_b, &g_c, 1, 12, 2},
	{ft_f, &g_c, &g_d, &g_a, &g_b, 2, 17, 3},
	{ft_f, &g_b, &g_c, &g_d, &g_a, 3, 22, 4},
	{ft_f, &g_a, &g_b, &g_c, &g_d, 4, 7, 5},
	{ft_f, &g_d, &g_a, &g_b, &g_c, 5, 12, 6},
	{ft_f, &g_c, &g_d, &g_a, &g_b, 6, 17, 7},
	{ft_f, &g_b, &g_c, &g_d, &g_a, 7, 22, 8},
	{ft_f, &g_a, &g_b, &g_c, &g_d, 8, 7, 9},
	{ft_f, &g_d, &g_a, &g_b, &g_c, 9, 12, 10},
	{ft_f, &g_c, &g_d, &g_a, &g_b, 10, 17, 11},
	{ft_f, &g_b, &g_c, &g_d, &g_a, 11, 22, 12},
	{ft_f, &g_a, &g_b, &g_c, &g_d, 12, 7, 13},
	{ft_f, &g_d, &g_a, &g_b, &g_c, 13, 12, 14},
	{ft_f, &g_c, &g_d, &g_a, &g_b, 14, 17, 15},
	{ft_f, &g_b, &g_c, &g_d, &g_a, 15, 22, 16}
};

/*
** stage 2
*/
t_params			g_params_stage_2[16] =
{
	{ft_g, &g_a, &g_b, &g_c, &g_d, 1, 5, 17},
	{ft_g, &g_d, &g_a, &g_b, &g_c, 6, 9, 18},
	{ft_g, &g_c, &g_d, &g_a, &g_b, 11, 14, 19},
	{ft_g, &g_b, &g_c, &g_d, &g_a, 0, 20, 20},
	{ft_g, &g_a, &g_b, &g_c, &g_d, 5, 5, 21},
	{ft_g, &g_d, &g_a, &g_b, &g_c, 10, 9, 22},
	{ft_g, &g_c, &g_d, &g_a, &g_b, 15, 14, 23},
	{ft_g, &g_b, &g_c, &g_d, &g_a, 4, 20, 24},
	{ft_g, &g_a, &g_b, &g_c, &g_d, 9, 5, 25},
	{ft_g, &g_d, &g_a, &g_b, &g_c, 14, 9, 26},
	{ft_g, &g_c, &g_d, &g_a, &g_b, 3, 14, 27},
	{ft_g, &g_b, &g_c, &g_d, &g_a, 8, 20, 28},
	{ft_g, &g_a, &g_b, &g_c, &g_d, 13, 5, 29},
	{ft_g, &g_d, &g_a, &g_b, &g_c, 2, 9, 30},
	{ft_g, &g_c, &g_d, &g_a, &g_b, 7, 14, 31},
	{ft_g, &g_b, &g_c, &g_d, &g_a, 12, 20, 32},
};

/*
** stage 3
*/
t_params			g_params_stage_3[16] =
{
	{ft_h, &g_a, &g_b, &g_c, &g_d, 5, 4, 33},
	{ft_h, &g_d, &g_a, &g_b, &g_c, 8, 11, 34},
	{ft_h, &g_c, &g_d, &g_a, &g_b, 11, 16, 35},
	{ft_h, &g_b, &g_c, &g_d, &g_a, 14, 23, 36},
	{ft_h, &g_a, &g_b, &g_c, &g_d, 1, 4, 37},
	{ft_h, &g_d, &g_a, &g_b, &g_c, 4, 11, 38},
	{ft_h, &g_c, &g_d, &g_a, &g_b, 7, 16, 39},
	{ft_h, &g_b, &g_c, &g_d, &g_a, 10, 23, 40},
	{ft_h, &g_a, &g_b, &g_c, &g_d, 13, 4, 41},
	{ft_h, &g_d, &g_a, &g_b, &g_c, 0, 11, 42},
	{ft_h, &g_c, &g_d, &g_a, &g_b, 3, 16, 43},
	{ft_h, &g_b, &g_c, &g_d, &g_a, 6, 23, 44},
	{ft_h, &g_a, &g_b, &g_c, &g_d, 9, 4, 45},
	{ft_h, &g_d, &g_a, &g_b, &g_c, 12, 11, 46},
	{ft_h, &g_c, &g_d, &g_a, &g_b, 15, 16, 47},
	{ft_h, &g_b, &g_c, &g_d, &g_a, 2, 23, 48},
};

/*
** stage 4
*/
t_params			g_params_stage_4[16] =
{
	{ft_i, &g_a, &g_b, &g_c, &g_d, 0, 6, 49},
	{ft_i, &g_d, &g_a, &g_b, &g_c, 7, 10, 50},
	{ft_i, &g_c, &g_d, &g_a, &g_b, 14, 15, 51},
	{ft_i, &g_b, &g_c, &g_d, &g_a, 5, 21, 52},
	{ft_i, &g_a, &g_b, &g_c, &g_d, 12, 6, 53},
	{ft_i, &g_d, &g_a, &g_b, &g_c, 3, 10, 54},
	{ft_i, &g_c, &g_d, &g_a, &g_b, 10, 15, 55},
	{ft_i, &g_b, &g_c, &g_d, &g_a, 1, 21, 56},
	{ft_i, &g_a, &g_b, &g_c, &g_d, 8, 6, 57},
	{ft_i, &g_d, &g_a, &g_b, &g_c, 15, 10, 58},
	{ft_i, &g_c, &g_d, &g_a, &g_b, 6, 15, 59},
	{ft_i, &g_b, &g_c, &g_d, &g_a, 13, 21, 60},
	{ft_i, &g_a, &g_b, &g_c, &g_d, 4, 6, 61},
	{ft_i, &g_d, &g_a, &g_b, &g_c, 11, 10, 62},
	{ft_i, &g_c, &g_d, &g_a, &g_b, 2, 15, 63},
	{ft_i, &g_b, &g_c, &g_d, &g_a, 9, 21, 64},
};

t_params			*g_p_stages[4] = {g_params_stage_1, g_params_stage_2,\
	g_params_stage_3, g_params_stage_4};

static void			init_buffers(void)
{
	size_t		i;

	g_a = 0x67452301;
	g_b = 0xEFCDAB89;
	g_c = 0x98BADCFE;
	g_d = 0x10325476;
	i = 0;
	while (i < g_size_const_arr)
	{
		g_t[i] = (unsigned)(0x100000000 * fabs(sin(i)));
		++i;
	}
}

static void			stage(t_string *str, size_t delta, t_params *params)
{
	size_t		i;

	i = 0;
	while (i < 16)
	{
		*(params[i].a) = *(params[i].b) + rotr_left((*(params[i].a) +
				params[i].f(*(params[i].b), *(params[i].c), *(params[i].d)) +
				((uint32_t*)(str->str))[delta + params[i].k] +
				g_t[params[i].i]), params[i].s);
		++i;
	}
}

static uint8_t		*init_hash(void)
{
	uint8_t		*hash;

	if (!(hash = (uint8_t*)ft_memalloc(g_md5_size * sizeof(uint8_t))))
		return (NULL);
	((uint32_t*)hash)[0] = g_a;
	((uint32_t*)hash)[1] = g_b;
	((uint32_t*)hash)[2] = g_c;
	((uint32_t*)hash)[3] = g_d;
	return (hash);
}

uint8_t				*calculate_md5(t_string *str)
{
	uint32_t	save[4];
	size_t		i;
	size_t		n;

	init_buffers();
	i = 0;
	while (i < (str->size / sizeof(uint32_t)))
	{
		save[0] = g_a;
		save[1] = g_b;
		save[2] = g_c;
		save[3] = g_d;
		n = 0;
		while (n < g_num_of_stages)
			stage(str, i, g_p_stages[n++]);
		g_a += save[0];
		g_b += save[1];
		g_c += save[2];
		g_d += save[3];
		i += 16;
	}
	return (init_hash());
}
