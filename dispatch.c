/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:49:04 by casautou          #+#    #+#             */
/*   Updated: 2019/09/14 15:49:05 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_wait	*dispatch(t_stock *stock, t_list *begin, t_paths *curr, t_wait *list)
{
	if (stock->io == 1)
	{
		while (curr)
		{
			if (check_sat(stock, curr->room->nu, begin->nu) == '1')
				list = check_add(stock, begin, curr, list);
			curr = curr->next;
		}
	}
	if (stock->io == 0)
	{
		while (curr)
		{
			if (check_sat(stock, begin->nu, curr->room->nu) == '0')
				list = check_add(stock, begin, curr, list);
			curr = curr->next;
		}
	}
	return (list);
}
