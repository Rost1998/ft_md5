/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:10:40 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:59:51 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "parser.h"

bool			g_was_exec = false;

static bool		del_queue(t_queue *queue)
{
	t_queue		*tmp;

	while (queue)
	{
		tmp = queue;
		queue = queue->next;
		free(tmp);
	}
	return (false);
}

static bool		exec_queue(t_queue **queue)
{
	t_queue		*tmp_q;

	while (*queue)
	{
		g_was_exec = true;
		if (!((*queue)->f(&(*queue)->options, (*queue)->info)))
			return (false);
		tmp_q = (*queue);
		(*queue) = (*queue)->next;
		free(tmp_q);
	}
	return (true);
}

static bool		parse_keys(char **argv, size_t *const i,\
							t_queue **queue, t_options *opt)
{
	int			j;
	size_t		ii;

	j = (int)*i;
	ii = 1;
	if (!argv[j][1])
		return ((bool)set_errno_and_ret(ERR_NONVALID_PARAM));
	while (argv[j] && argv[j][ii])
	{
		if (argv[j][ii] == 'q')
			opt->quiet = true;
		else if (argv[j][ii] == 'r')
			opt->reverse = true;
		else if (argv[j][ii] == 'p')
			add_to_queue_p(queue, opt);
		else if (argv[j][ii] == 's' && ++*i)
			add_to_queue_s(queue, opt, argv[*i]);
		else
			return ((bool)set_errno_and_ret(ERR_NONVALID_PARAM));
		++ii;
	}
	return (true);
}

bool			parse_args(t_options *opt, int argc, char **argv)
{
	t_queue		*queue;
	size_t		i;

	i = 2;
	queue = NULL;
	while ((int)i < argc && argv[i])
	{
		if (argv[i][0] == '-')
		{
			if (!parse_keys(argv, &i, &queue, opt))
				return (del_queue(queue));
		}
		else
			add_to_queue_file(&queue, opt, argv[i]);
		if (!(exec_queue(&queue)))
			return (del_queue(queue));
		++i;
	}
	if (!g_was_exec)
		handle_default(opt);
	return (true);
}
