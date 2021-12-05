/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:49:17 by casautou          #+#    #+#             */
/*   Updated: 2019/09/14 15:49:18 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	sort_int_tab(t_stock *stock, int i)
{
	int j;
	int sto;

	j = 0;
	while (j < i - 1)
	{
		if (stock->tab[j] > stock->tab[j + 1])
		{
			sto = stock->tab[j];
			stock->tab[j] = stock->tab[j + 1];
			stock->tab[j + 1] = sto;
			j = 0;
		}
		j++;
	}
}

void	check_turn_next(t_stock *stock, int fourmi, int i, int j)
{
	while (fourmi < stock->ant)
	{
		while (j < i - 1)
		{
			while (stock->tab[j] < stock->tab[j + 1])
			{
				stock->tab[j]++;
				stock->turn++;
				fourmi = fourmi + j + 1;
			}
			j++;
		}
		stock->turn++;
		fourmi = fourmi + j + 1;
	}
	if (stock->tab)
		free(stock->tab);
}

void	check_turn(t_stock *stock, int i)
{
	int j;
	int fourmi;
	int	saoul;

	saoul = stock->tab[0];
	fourmi = 0;
	stock->turn = 0;
	j = 0;
	check_turn_next(stock, fourmi, i, j);
	stock->turn = stock->turn + saoul - 1;
	if (stock->besturn > stock->turn)
		stock->besturn = stock->turn;
	else
	{
		remove_flow(stock);
		stock->stop = 1;
	}
}

void	opti_path_next(t_stock *stock, t_list *begin, t_paths *curr, int i)
{
	int count;

	count = 1;
	begin = curr->room;
	while (begin->end != 1)
	{
		curr = begin->path;
		while (stock->matrix[begin->nu][curr->room->nu] == '0'
		|| curr->room->nu == stock->cprev)
			curr = curr->next;
		count++;
		stock->cprev = begin->nu;
		begin = curr->room;
	}
	stock->tab[i] = count;
}

void	opti_path(t_stock *stock, t_list *begin)
{
	t_paths	*curr;
	int		i;

	i = 0;
	if (!(stock->tab = (int*)malloc(sizeof(int) * stock->ref)))
		return ;
	curr = begin->path;
	while (curr)
	{
		stock->cprev = begin->nu;
		if (stock->matrix[begin->nu][curr->room->nu] == '1'
		&& curr->room->nu != stock->cprev)
		{
			opti_path_next(stock, begin, curr, i);
			i++;
		}
		curr = curr->next;
	}
	sort_int_tab(stock, i);
	check_turn(stock, i);
}
