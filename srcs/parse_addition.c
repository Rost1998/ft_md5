/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_addition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:10:32 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:55:46 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"
#include "parser.h"

int			set_errno_and_ret(int err)
{
	errno = err;
	return (0);
}

t_queue		*ft_create_queue_node(void)
{
	t_queue		*new;

	if (!(new = (t_queue*)ft_memalloc(sizeof(t_queue))))
		return (NULL);
	new->f = NULL;
	new->info = NULL;
	new->next = NULL;
	return (new);
}
