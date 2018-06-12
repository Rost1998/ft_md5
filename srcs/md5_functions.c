/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:10:11 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 19:10:12 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	ft_f(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | (~x & z));
}

uint32_t	ft_g(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | (~z & y));
}

uint32_t	ft_h(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x ^ y ^ z));
}

uint32_t	ft_i(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (~z | x));
}
