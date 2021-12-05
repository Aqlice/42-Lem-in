/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:48:49 by casautou          #+#    #+#             */
/*   Updated: 2019/09/14 15:48:51 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reverse_list(t_list *begin, t_stock *stock)
{
	t_list *next;
	t_list *curr;
	t_list *prev;

	curr = begin;
	next = NULL;
	prev = NULL;
	stock->find = begin;
	while (curr)
	{
		next = curr->prev;
		curr->prev = prev;
		prev = curr;
		curr = next;
	}
	begin = prev;
	stock->find = begin;
	stock->sat = begin;
}
