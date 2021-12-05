/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:05:23 by casautou          #+#    #+#             */
/*   Updated: 2019/09/19 15:05:25 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_to(t_list *path)
{
	while (path)
	{
		path->nu = 0;
		path = path->p;
	}
}

void	set_start(t_stock *stock, t_list *prev)
{
	if (stock->abp[stock->i] <= 0)
		return ;
	if (stock->fourmi > stock->ant)
		return ;
	stock->abp[stock->i]--;
	if (!(stock->first == 0))
		ft_printf(" ");
	if (stock->first == 0)
		stock->first++;
	ft_printf("L%d-%s", stock->fourmi, prev->n);
	prev->nu = stock->fourmi;
	stock->fourmi++;
}

void	aff_next_next(t_stock *stock, t_list *path, t_list *prev)
{
	while (path)
	{
		if (path->start == 1)
			set_start(stock, prev);
		if (path->nu != 0)
		{
			if (!(stock->first == 0))
				ft_printf(" ");
			if (stock->first == 0)
				stock->first++;
			ft_printf("L%d-%s", path->nu, prev->n);
			prev->nu = path->nu;
			path->nu = 0;
		}
		prev = path;
		path = path->p;
	}
}

void	aff_next(t_stock *stock, t_list *begin, t_list *path)
{
	t_list	*prev;

	path = begin->fpath;
	stock->j = 0;
	stock->turn = 0;
	stock->fourmi = 1;
	while (1)
	{
		stock->first = 0;
		stock->i = 0;
		while (stock->i < stock->flow)
		{
			prev = begin;
			path = begin->fpath;
			while (stock->j++ < stock->i)
				path = path->fnext;
			aff_next_next(stock, path, prev);
			stock->j = 0;
			stock->i++;
		}
		stock->turn++;
		ft_printf("\n");
		if (stock->turn == stock->besturn)
			break ;
	}
}

void	aff(t_stock *stock)
{
	t_list	*begin;
	t_list	*path;
	int		fourmi;

	stock->i = -1;
	fourmi = 1;
	begin = stock->real_begin;
	while (begin->end != 1)
		begin = begin->next;
	while (stock->i++ < stock->flow)
	{
		stock->j = 0;
		path = begin->fpath;
		while (stock->j++ < stock->i)
			path = path->fnext;
		set_to(path);
	}
	aff_next(stock, begin, path);
}
