/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:21:41 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/11/05 13:05:34 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mystrlen(const char *s)
{
	int		i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

char		*ft_strdup(const char *s)
{
	char	*text;
	char	*st;

	if (!s)
		return NULL;
	if (!(text = (char*)malloc((mystrlen(s) + 1) * sizeof(char))))
		return (0);
	st = text;
	while (*s != '\0')
		*text++ = *s++;
	*text = 0;
	return (st);
}
