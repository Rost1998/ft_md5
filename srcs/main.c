/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:09:46 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:39:35 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		print_usage(void)
{
	write(1, "usage:\t./ft_ssl commands [command opts]\n", 40);
}

static void		err_handle(void)
{
	char	*err;

	if (errno == ERR_FILE_NOT_OPEN)
		err = "Error: File not open\n";
	else if (errno == ERR_INCORRECT_ARG)
		err = "Error: Incorrect argument\n";
	else if (errno == ERR_INCORRECT_FILENAME)
		err = "Error: Incorrect filename\n";
	else if (errno == ERR_NONVALID_PARAM)
		err = "Error: Nonvalid param\n";
	else if (errno == ERR_NOT_ENOUGH_PARAMS)
		err = "Error: Not enough params\n";
	else if (errno == ERR_UNKNOWN_COMMAND)
		err = "Error: Unknown command\n";
	else if (errno == ERR_FILE_READ_ERR)
		err = "Error: File read error\n";
	else
		err = "Error: Unknown error\n";
	write(1, err, ft_strlen(err));
}

int				main(int argc, char **argv)
{
	bool	done;
	int		ret;

	ret = 0;
	if (argc == 1)
	{
		print_usage();
		return (ret);
	}
	errno = ERR_DEFAULT_ERRNO;
	done = parse(argc, argv);
	if (!done)
	{
		err_handle();
		ret = 1;
	}
	return (ret);
}
