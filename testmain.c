/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 12:16:10 by dapinto           #+#    #+#             */
/*   Updated: 2019/08/30 13:51:06 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_parse	container;
	t_list	*begin;
	char *s;
	int fd;
	int i;

	s = argv[1];
	if (argc == 2)
		container.verbose = (!ft_strcmp(s, "-v")
				|| !ft_strcmp(s, "-verbose")) ? 1 : 0;
	i = 1;
	while (argv[i])
	{
		begin = NULL;
		ft_bzero(&container, sizeof(t_parse));
		if (!(fd = open(argv[i], O_RDONLY)))
		{
			free_list(&begin);
			close(fd);
			return (-1);
		}
		if (!(begin = anthill_info_parser(fd, &container)))
		{
			close(fd);
			return (-1);
		}
		if (close(fd) == -1)
		{
			free_list(&begin);
			close(fd);
			return (-1);
		}
		free_list(&begin);
		i++;
	}
	return (0);
}
