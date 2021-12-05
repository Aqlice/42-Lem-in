/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_info_saver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:09:12 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/23 13:16:59 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			printhash(t_parse *box)
{
	int		i;
	t_hash	*hash;

	i = 0;
	while (i < box->room_nb)
	{
		if (box->room_ids[i].room != NULL)
		{
			hash = &box->room_ids[i];
			ft_printf("Hash_index[%d]->|%s|\n", i, hash->room);
			while (hash->next_col)
			{
				hash = hash->next_col;
				ft_printf("Collision with |%s|\n", hash->room);
			}
		}
		i++;
	}
}

static int		save_room_names(t_parse *box, int room_nb)
{
	int c;
	int i;

	c = 0;
	i = box->room_i;
	if (!room_nb
			|| !(box->room_ids = ft_memalloc(sizeof(t_hash) * room_nb + 1)))
		return (-1);
	while (c < room_nb)
	{
		if (ft_strcmp(box->input[i], "") != 0)
		{
			if (hashtable(box, box->input[i], i) == -1)
				return (-1);
			c++;
		}
		i++;
	}
	return (0);
}

static int		format_validity(t_parse *box, char *line, int i)
{
	if (ft_strcmp(line, "") == 0 || ft_strcmp(START, line) == 0
			|| ft_strcmp(END, line) == 0)
		return (0);
	else if (ft_str_nb_of_target(line, " ") == 2
			&& ft_strisdigit(ft_strrchr(line, ' ') + 1)
			&& ft_strisdigit(ft_strchr(line, ' ') + 1)
			&& ft_count_word(line, ' ') == 3
			&& assert_no_duplicate(box, line, i + 1)
			&& *line != 'L')
	{
		box->room_nb++;
		return (1);
	}
	else
		return (-1);
	return (-1);
}

int				room_description(t_parse *box)
{
	int i;

	i = box->room_i;
	while (box->input[i] && !ft_strchr(box->input[i], '-'))
	{
		if (format_validity(box, box->input[i], i) == -1)
		{
			errout(box->verbose,
					"ERROR: Room format invalid. Check duplicates/spacing.");
			return (-1);
		}
		i++;
	}
	if (!box->input[i] || save_room_names(box, box->room_nb) == -1)
	{
		errout(box->verbose,
				"ERROR: Failed to find links or to hash rooms.");
		return (-1);
	}
	return (1);
}
