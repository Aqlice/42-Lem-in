/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:59:33 by casautou          #+#    #+#             */
/*   Updated: 2019/09/19 14:59:36 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_abp_next(t_stock *stock, int fourmi)
{
	stock->stop = 0;
	stock->i = 0;
	while (fourmi < stock->ant)
	{
		while (stock->i < stock->flow)
		{
			stock->abp[stock->i]++;
			stock->i++;
			fourmi++;
			if (fourmi == stock->ant)
			{
				stock->stop = 1;
				break ;
			}
		}
		stock->i = 0;
		if (stock->stop == 1)
			break ;
	}
}

void	get_abp(t_stock *stock)
{
	int fourmi;

	stock->i = 0;
	stock->j = stock->flow - 1;
	fourmi = 0;
	while (stock->i++ < stock->flow)
		stock->abp[stock->i] = 0;
	stock->i = 0;
	while (stock->i <= stock->j)
	{
		stock->abp[stock->i] = stock->tab[stock->j] - stock->tab[stock->i];
		stock->i++;
	}
	stock->i = 0;
	while (stock->i < stock->j)
	{
		fourmi = fourmi + stock->abp[stock->i];
		stock->i++;
	}
	get_abp_next(stock, fourmi);
}
