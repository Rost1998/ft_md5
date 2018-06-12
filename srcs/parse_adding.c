/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_adding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:10:23 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:42:39 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	add_elem(t_queue **queue, t_options *opt,\
								t_arg_function f, char *info)
{
	t_queue		*tmp;
	t_queue		*new_elem;

	new_elem = ft_create_queue_node();
	new_elem->f = f;
	new_elem->info = info;
	new_elem->options.cmd = opt->cmd;
	new_elem->options.reverse = opt->reverse;
	new_elem->options.quiet = opt->quiet;
	if (!*queue)
		*queue = new_elem;
	else
	{
		tmp = *queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
}

void		add_to_queue_p(t_queue **queue, t_options *opt)
{
	add_elem(queue, opt, handle_p, NULL);
}

void		add_to_queue_file(t_queue **queue, t_options *opt, char *filename)
{
	add_elem(queue, opt, handle_file, filename);
}

void		add_to_queue_s(t_queue **queue, t_options *opt, char *next_arg)
{
	add_elem(queue, opt, handle_s, next_arg);
}
