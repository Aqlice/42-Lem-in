/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:46:49 by casautou          #+#    #+#             */
/*   Updated: 2019/09/14 15:47:38 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	apply_flow(t_stock *stock, t_list *begin)
{
	t_list	*a;

	a = stock->find;
	begin = stock->find;
	stock->prevsaturated = stock->matrix[a->nu][a->prev->nu];
	while (a->end != 1)
	{
		if (stock->matrix[a->prev->nu][a->nu] == '1')
			stock->matrix[a->prev->nu][a->nu] = '0';
		else if (stock->matrix[a->nu][a->prev->nu] == '0')
			stock->matrix[a->nu][a->prev->nu] = '1';
		if (stock->prevsaturated == stock->matrix[a->nu][a->prev->nu])
		{
			if (stock->matrix[a->nu][a->nu] == '1')
				stock->matrix[a->nu][a->nu] = '0';
			else
				stock->matrix[a->nu][a->nu] = '1';
		}
		stock->prevsaturated = stock->matrix[a->nu][a->prev->nu];
		a = a->prev;
	}
}

void	remove_flow(t_stock *stock)
{
	t_list	*a;

	a = stock->sat;
	stock->prevsaturated = stock->matrix[a->nu][a->prev->nu];
	while (a->end != 1)
	{
		if (stock->matrix[a->nu][a->prev->nu] == '1')
			stock->matrix[a->nu][a->prev->nu] = '0';
		else
			stock->matrix[a->prev->nu][a->nu] = '1';
		a = a->prev;
	}
}
