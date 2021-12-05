/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:55:16 by casautou          #+#    #+#             */
/*   Updated: 2019/09/19 14:55:20 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	cut_end(t_stock *stock)
{
	t_list *begin;

	begin = stock->real_begin;
	while (begin->end != 1)
		begin = begin->next;
	begin->path = NULL;
}

void	add_path(t_list *begin, t_list *prev)
{
	t_list	*real_begin;

	real_begin = begin->fpath;
	if (!(begin->fpath))
	{
		begin->fpath = prev;
		begin->fpath->fnext = NULL;
	}
	else
	{
		while (begin->fpath->fnext)
			begin->fpath = begin->fpath->fnext;
		begin->fpath->fnext = prev;
		prev->fnext = NULL;
		begin->fpath = real_begin;
	}
}

void	reverse_paths(t_list *begin)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*real_begin;
	t_list	*next;

	real_begin = begin;
	curr = begin->pfnext;
	while (curr)
	{
		prev = real_begin;
		begin = curr;
		while (begin->end != 1)
		{
			next = begin->p;
			begin->p = prev;
			prev = begin;
			begin = next;
		}
		add_path(begin, prev);
		curr = curr->pfnext;
	}
}
