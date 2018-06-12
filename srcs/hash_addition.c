/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_addition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:09:23 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 19:09:26 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned		rotr_left(unsigned a, int offset)
{
	return ((a << offset) | (a >> (32 - offset)));
}

unsigned		rotr_right(unsigned a, int offset)
{
	return ((a >> offset) | (a << (32 - offset)));
}
