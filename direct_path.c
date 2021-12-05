/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:39:27 by casautou          #+#    #+#             */
/*   Updated: 2019/09/24 18:39:28 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_direct_path(t_list *begin, t_paths *curr)
{
	int i;

	i = 1;
	while (i < begin->ant_nb)
	{
		ft_printf("L%d-%s ", i, curr->room->n);
		i++;
	}
	ft_printf("L%d-%s\n", i, curr->room->n);
}

int		direct_path(t_list *begin, t_stock *stock)
{
	t_paths *curr;

	curr = begin->path;
	while (curr)
	{
		if (curr->room->end == 1)
		{
			print_direct_path(begin, curr);
			free_all(stock);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}
