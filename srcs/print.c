/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:11:11 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:52:56 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char		*get_hex_byte(uint8_t byte)
{
	char	*hex;

	hex = ft_itoa_base(byte, 16);
	if (ft_strlen(hex) == 1)
	{
		hex = ft_realloc_modf(hex, 3, 2);
		*(hex + 1) = *hex;
		*hex = '0';
	}
	return (hex);
}

static void		print_info(t_options *opt, t_string *to_print)
{
	if (opt->cmd == e_cmd_md5)
		write(1, "MD5 (", 5);
	else if (opt->cmd == e_cmd_sha256)
		write(1, "SHA256 (", 8);
	write(1, to_print->str, to_print->size);
	write(1, ") ", 2);
}

void			print_hash(uint8_t *hash, t_options *opt,\
								t_string *to_print, bool flag_p)
{
	size_t		i;
	size_t		size_hash;
	char		*hex;

	size_hash = opt->cmd == e_cmd_md5 ? 16 : 32;
	if (!opt->reverse && !opt->quiet && !flag_p)
		print_info(opt, to_print);
	i = 0;
	while (i < size_hash)
	{
		hex = get_hex_byte(hash[i]);
		write(1, hex, ft_strlen(hex));
		free(hex);
		++i;
	}
	if (opt->reverse && !opt->quiet && !flag_p)
	{
		write(1, " ", 1);
		print_info(opt, to_print);
	}
	write(1, "\n", 1);
}
