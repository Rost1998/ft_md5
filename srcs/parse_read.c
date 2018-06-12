/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:11:05 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:52:16 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_ssl.h"
#include "parser.h"

const int			g_stdin_buff_size = 1024;

static t_string		*read_from(int fd)
{
	char		tmp_buff[g_stdin_buff_size];
	char		*buff;
	ssize_t		size;
	size_t		len;
	t_string	*ret;

	buff = (char*)ft_memalloc(1 * sizeof(char));
	len = 0;
	while ((size = read(fd, tmp_buff, g_stdin_buff_size)))
	{
		if (size < 0)
		{
			free(buff);
			return (false);
		}
		buff = ft_realloc_modf(buff, sizeof(char) *
						(len + size + 1), sizeof(char) * len);
		ft_memcpy(buff + len, tmp_buff, size);
		len += size;
	}
	if (!(ret = (t_string*)ft_memalloc(sizeof(t_string))))
		return (NULL);
	ret->str = buff;
	ret->size = len;
	return (ret);
}

void				read_from_stdin(t_options *opt)
{
	opt->input = read_from(0);
}

bool				read_from_file(t_options *opt, char *filename)
{
	int			fd;
	t_string	*input;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return ((bool)set_errno_and_ret(ERR_FILE_NOT_OPEN));
	if (!(input = read_from(fd)))
		return ((bool)set_errno_and_ret(ERR_FILE_READ_ERR));
	opt->input = input;
	return (true);
}
