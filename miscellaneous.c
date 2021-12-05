/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:13:38 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/23 14:02:30 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		comment_clean(t_parse *box, int com_nb)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (box->input[i] && c < com_nb)
	{
		if (*box->input[i] == '#'
				&& (ft_strcmp(box->input[i], START) != 0
					&& ft_strcmp(box->input[i], END) != 0))
		{
			ft_strclr(box->input[i]);
			c++;
		}
		i++;
	}
	return (0);
}

int		hash(t_parse *box, char *room, size_t len)
{
	size_t	i;
	int		sum;

	i = 0;
	sum = 0;
	while (i < len)
	{
		sum += room[i];
		i++;
	}
	sum %= box->room_nb;
	return (sum);
}
