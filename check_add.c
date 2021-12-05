/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:48:57 by casautou          #+#    #+#             */
/*   Updated: 2019/09/14 15:48:58 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_wait	*check_add(t_stock *stock, t_list *begin, t_paths *curr, t_wait *list)
{
	if (stock->io == 1 && curr->room->end == 1)
		return (list);
	if (begin->start != 1)
		if (curr->room->nu == begin->prev->nu)
			return (list);
	if (stock->io == 1)
		if (curr->room->mark != stock->ref)
		{
			curr->room->mark = stock->ref;
			curr->room->prev = begin;
			return (add_list(stock, curr->room, list, 0));
		}
	if (stock->io == 0)
		if (curr->room->mark != stock->ref)
		{
			curr->room->mark = stock->ref;
			curr->room->prev = begin;
			return (add_list(stock, curr->room, list, 1));
		}
	return (list);
}
