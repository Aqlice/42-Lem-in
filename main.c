/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 12:16:10 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/19 17:26:40 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_parse	container;
	t_list	*begin;
	t_stock	stock;
	
	begin = NULL;
	ft_bzero(&stock, sizeof(t_stock));
	ft_bzero(&container, sizeof(t_parse));
	if (argc == 2)
		container.verbose = (!ft_strcmp(argv[1], "-v")
				|| !ft_strcmp(argv[1], "-verbose")) ? 1 : 0;
	if (!(begin = anthill_info_parser(STDIN_FILENO, &container)))
		return (-1);
	karp(&stock, begin);
	free_list(&begin);
	return (0);
}
