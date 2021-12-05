/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:59:10 by casautou          #+#    #+#             */
/*   Updated: 2019/09/19 14:59:17 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	change_positions(t_stock *stock, t_list *curr,
t_list *begin, t_list *prev)
{
	int		s;
	t_list	*next;

	if (curr == begin->pfpath)
	{
		prev = begin->pfpath;
		next = begin->pfpath->pfnext->pfnext;
		begin->pfpath = curr->pfpath->pfnext;
		prev->pfnext = next;
		begin->pfnext = prev;
	}
	else
	{
		prev->pfnext = curr->pfnext;
		curr->pfnext = curr->pfnext->pfnext;
		prev->pfnext->pfnext = curr;
	}
	s = stock->tab[stock->i];
	stock->tab[stock->i] = stock->tab[stock->i + 1];
	stock->tab[stock->i + 1] = s;
}

void	sort_list(t_stock *stock, t_list *begin)
{
	t_list	*curr;
	t_list	*prev;

	stock->i = 0;
	prev = NULL;
	curr = begin->pfnext;
	while (stock->i < stock->flow - 1)
	{
		if (stock->tab[stock->i] > stock->tab[stock->i + 1])
		{
			change_positions(stock, curr, begin, prev);
			curr = begin->pfnext;
			stock->i = 0;
		}
		else
		{
			prev = curr;
			curr = curr->pfnext;
			stock->i++;
		}
	}
}

void	cut_paths(t_stock *stock, t_list *begin)
{
	t_paths *curr;

	curr = begin->path;
	while (curr)
	{
		if (stock->matrix[begin->nu][curr->room->nu] == '1')
			add_another_path(begin, curr);
		curr = curr->next;
	}
}

void	prepare_path(t_stock *stock, t_list *begin, t_list *path, int i)
{
	int		length;
	t_list	*real_begin;
	t_paths	*curr;

	real_begin = begin;
	length = 1;
	begin = path;
	while (begin->end != 1)
	{
		curr = begin->path;
		while (stock->matrix[begin->nu][curr->room->nu] != '1')
			curr = curr->next;
		begin->p = curr->room;
		begin = curr->room;
		length++;
	}
	stock->tab[i] = length;
}

void	get_in_line(t_stock *stock, t_list *begin)
{
	int		i;
	t_list	*path;

	i = 0;
	if (!(stock->tab = (int*)malloc(sizeof(int) * (stock->flow + 1))))
		return ;
	if (!(stock->abp = (int*)malloc(sizeof(int) * (stock->flow + 1))))
		return ;
	while (begin->start != 1)
		begin = begin->next;
	cut_paths(stock, begin);
	path = begin->pfnext;
	while (i < stock->flow)
	{
		prepare_path(stock, begin, path, i);
		i++;
		path = path->pfnext;
	}
	sort_list(stock, begin);
	get_abp(stock);
	reverse_paths(begin);
	aff(stock);
	free_all(stock);
}
