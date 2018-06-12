/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 22:17:57 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 22:21:48 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_PARSER_H
# define MD5_PARSER_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include "ft_ssl.h"
# include "errors.h"

typedef enum		e_command
{
	e_cmd_unknown = -1,
	e_cmd_md5,
	e_cmd_sha256
}					t_cmd;

typedef struct		s_options
{
	t_string		*input;
	t_cmd			cmd;
	bool			quiet;
	bool			reverse;
}					t_options;

typedef bool		(*t_arg_function)(t_options *, char *);

typedef struct		s_queue
{
	t_arg_function	f;
	t_options		options;
	char			*info;
	struct s_queue	*next;
}					t_queue;

bool				parse(int argc, char **argv);
bool				parse_args(t_options *opt, int argc, char **argv);
void				read_from_stdin(t_options *opt);
bool				read_from_file(t_options *opt, char *filename);
t_queue				*ft_create_queue_node(void);
bool				handle_p(t_options *opt, char *info);
bool				handle_file(t_options *opt, char *filename);
bool				handle_s(t_options *opt, char *next_arg);
bool				handle_default(t_options *opt);
int					set_errno_and_ret(int err);
void				add_to_queue_p(t_queue **queue, t_options *opt);
void				add_to_queue_file(t_queue **queue, t_options *opt,\
															char *filename);
void				add_to_queue_s(t_queue **queue, t_options *opt,\
															char *next_arg);
void				print_hash(uint8_t *hash, t_options *opt,\
											t_string *to_print, bool flag_p);

#endif
