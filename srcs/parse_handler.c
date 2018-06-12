/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 19:10:49 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/06/10 21:51:15 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "parser.h"

bool		handle_default(t_options *opt)
{
	uint8_t		*hash;
	t_string	fn;

	hash = NULL;
	read_from_stdin(opt);
	if (!(fn.str = (char*)ft_memalloc(opt->input->size * sizeof(char))))
		return (false);
	ft_memcpy(fn.str, opt->input->str, opt->input->size);
	fn.size = opt->input->size;
	if (opt->cmd == e_cmd_md5)
		hash = md5(opt->input);
	else if (opt->cmd == e_cmd_sha256)
		hash = sha256(opt->input);
	if (!hash)
		return ((bool)set_errno_and_ret(ERR_UNKNOWN_ERR));
	opt->quiet = true;
	print_hash(hash, opt, &fn, false);
	free(fn.str);
	free(opt->input->str);
	free(opt->input);
	free(hash);
	return (true);
}

bool		handle_p(t_options *opt, char *info)
{
	uint8_t		*hash;
	t_string	fn;

	(void)info;
	hash = NULL;
	read_from_stdin(opt);
	if (!(fn.str = (char*)ft_memalloc(opt->input->size * sizeof(char))))
		return (false);
	ft_memcpy(fn.str, opt->input->str, opt->input->size);
	fn.size = opt->input->size;
	if (opt->cmd == e_cmd_md5)
		hash = md5(opt->input);
	else if (opt->cmd == e_cmd_sha256)
		hash = sha256(opt->input);
	if (!hash)
		return ((bool)set_errno_and_ret(ERR_UNKNOWN_ERR));
	write(1, fn.str, fn.size);
	print_hash(hash, opt, &fn, true);
	free(fn.str);
	free(opt->input->str);
	free(opt->input);
	free(hash);
	return (true);
}

bool		handle_file(t_options *opt, char *filename)
{
	uint8_t		*hash;
	t_string	fn;

	hash = NULL;
	if (!filename)
		return ((bool)set_errno_and_ret(ERR_INCORRECT_FILENAME));
	if (!(read_from_file(opt, filename)))
		return (false);
	if (opt->cmd == e_cmd_md5)
		hash = md5(opt->input);
	else if (opt->cmd == e_cmd_sha256)
		hash = sha256(opt->input);
	if (!hash)
		return ((bool)set_errno_and_ret(ERR_UNKNOWN_ERR));
	fn.str = filename;
	fn.size = ft_strlen(filename);
	print_hash(hash, opt, &fn, false);
	free(opt->input->str);
	free(opt->input);
	free(hash);
	return (true);
}

bool		handle_s(t_options *opt, char *next_arg)
{
	uint8_t		*hash;
	t_string	fn;

	hash = NULL;
	if (!next_arg)
		return ((bool)set_errno_and_ret(ERR_INCORRECT_ARG));
	if (!(opt->input = (t_string*)ft_memalloc(sizeof(t_string))))
		return (false);
	opt->input->str = ft_strdup(next_arg);
	opt->input->size = ft_strlen(next_arg);
	fn.str = next_arg;
	fn.size = opt->input->size;
	if (opt->cmd == e_cmd_md5)
		hash = md5(opt->input);
	else if (opt->cmd == e_cmd_sha256)
		hash = sha256(opt->input);
	if (!hash)
		return ((bool)set_errno_and_ret(ERR_UNKNOWN_ERR));
	print_hash(hash, opt, &fn, false);
	free(opt->input->str);
	free(opt->input);
	free(hash);
	return (true);
}
