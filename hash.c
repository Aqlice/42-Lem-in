/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:24:45 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/23 15:04:56 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_hash	*create_collision(char *r)
{
	t_hash *node;

	if (!(node = ft_memalloc(sizeof(t_hash))))
		return (NULL);
	if (!(node->room = ft_strsub(r, 0, ft_strichr(r, ' '))))
		return (NULL);
	return (node);
}

static t_hash	*handle_collisions(t_hash *hash, char *r)
{
	t_hash *ptr;

	ptr = hash;
	while (ptr->next_col)
		ptr = ptr->next_col;
	if (!(ptr->next_col = create_collision(r)))
		return (NULL);
	return (ptr->next_col);
}

static int		assign(t_parse *box, int i, char *room, int startend)
{
	t_hash *ptr;

	ptr = &box->room_ids[i];
	if (ptr->room == NULL)
	{
		if (!(ptr->room = ft_strsub(room, 0, ft_strichr(room, ' '))))
			return (-1);
	}
	else if (!(ptr = handle_collisions(ptr, room)))
		return (-1);
	ptr->startend = startend;
	return (0);
}

static char		*fetchroom(t_parse *box, char *input, int i, int *mod_fg)
{
	int start;

	start = 0;
	start = ft_strcmp(input, START);
	*mod_fg = (!start) ? 1 : 2;
	while (!*box->input[i])
		i++;
	return (box->input[i]);
}

int				hashtable(t_parse *box, char *room, int r_index)
{
	int		i;
	char	*r;
	int		startend;

	r = room;
	startend = 0;
	if (ft_strcmp(room, START) == 0 || ft_strcmp(room, END) == 0)
		if (!(r = fetchroom(box, room, r_index + 1, &startend)))
			return (-1);
	i = hash(box, r, ft_strichr(r, ' '));
	if (assign(box, i, r, startend) == -1)
		return (-1);
	ft_strclr(r);
	ft_strclr(room);
	return (0);
}
