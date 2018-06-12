/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 22:17:53 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 22:22:34 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <zconf.h>
# include <stdbool.h>
# include <errno.h>
# include "libft.h"

# define BYTE_SIZE 8

typedef uint32_t	(*t_func)(uint32_t, uint32_t, uint32_t);

typedef struct		s_string
{
	char			*str;
	size_t			size;
}					t_string;

typedef struct		s_params
{
	t_func			f;
	uint32_t		*a;
	uint32_t		*b;
	uint32_t		*c;
	uint32_t		*d;
	uint32_t		k;
	uint32_t		s;
	uint32_t		i;
}					t_params;

uint32_t			ft_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t			ft_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t			ft_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t			ft_i(uint32_t x, uint32_t y, uint32_t z);

uint8_t				*md5(t_string *input);
uint8_t				*sha256(t_string *input);
bool				align_str(t_string *str);
uint8_t				*calculate_md5(t_string *str);
uint8_t				*calculate_sha256(uint32_t **blocks);
uint16_t			reverse_2_bytes(uint16_t b);
uint32_t			reverse_4_bytes(uint32_t b);
unsigned			rotr_left(unsigned a, int offset);
unsigned			rotr_right(unsigned a, int offset);
uint32_t			**get_blocks(t_string *str);
void				change_len(t_string *str);
void				init(void);

#endif
