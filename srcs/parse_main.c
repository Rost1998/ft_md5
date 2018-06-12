/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:10:58 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 22:08:07 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "parser.h"

t_cmd			parse_command(char *cmd)
{
	char const *const	cmds[2] = {"md5", "sha256"};
	int					i;

	i = 0;
	while (i < 2)
	{
		if (!ft_strcmp(cmd, cmds[i]))
			return ((t_cmd)i);
		++i;
	}
	return (e_cmd_unknown);
}

bool			parse(int argc, char **argv)
{
	t_options	opt;

	opt.quiet = 0;
	opt.reverse = 0;
	opt.cmd = e_cmd_unknown;
	if (argc < 2)
		return ((bool)set_errno_and_ret(ERR_NOT_ENOUGH_PARAMS));
	if ((opt.cmd = parse_command(argv[1])) == e_cmd_unknown)
		return ((bool)set_errno_and_ret(ERR_UNKNOWN_COMMAND));
	if (!(parse_args(&opt, argc, argv)))
		return (false);
	return (true);
}
