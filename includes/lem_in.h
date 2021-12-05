/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:37:00 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/19 17:23:38 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# define START "##start"
# define END "##end"

typedef struct	s_stock
{
	int				io;
	int				room;
	int				max;
	int				ant;
	int				flow;
	int				ref;
	int				f;
	int				size;
	int				stop;
	struct s_wait	*update;
	struct s_list	*find;
	struct s_list	*final;
	struct s_wait	*free;
	struct s_list	*sat;
	struct s_list	*real_begin;

	int			i;
	int			j;
	char		prevsaturated;
	int			node;
	struct 		s_final *temp;
	int			*tab;
	int			*abp;
	int			turn;
	int			besturn;
	int			cprev;
	char		**matrix;
	int			fourmi;
	int			first;
}				t_stock;

typedef struct	s_paths
{
	int				nu;
	char			*n;
	int				io;
	int				saturated;
	struct s_paths	*next;
	struct s_list	*room;
}				t_paths;

typedef struct	s_list
{
	int				nu;
	char			*n;
	int				start;
	int				end;
	int				mark;
	int				saturated;
	long			ant_nb;
	struct s_list	*next;
	struct s_list	*find;
	struct s_paths	*path;
	struct s_list	*prev;
	struct s_list	*fpath;
	struct s_list	*pfpath;
	struct s_list	*pfnext;
	struct s_list	*fnext;

	struct s_list	*p;
}				t_list;

typedef struct	s_hash
{
	char			*room;
	int				startend;
	struct s_hash	*next_col;
}				t_hash;

typedef struct	s_wait
{
	struct s_list	*point;
	struct s_wait	*next;
	int				io;
}				t_wait;

typedef struct	s_parse_container
{
	long			ant_nb;
	int				room_nb;
	int				link_i;
	int				room_i;
	int				ants_i;
	int				verbose;
	char			*room1;
	char			*room2;
	t_hash			*room_ids;
	char			**output;
	char			**input;
}				t_parse;

void			max_flow(t_stock *stock, t_list *begin);
void			apply_flow(t_stock *stock, t_list *begin);
void			reverse_list(t_list *begin, t_stock *stock);
t_list			*anthill_info_parser(int fd, t_parse *container);
int				input_check(t_parse *box);
int				assert_validity(t_parse *box, int i);
int				assert_no_duplicate(t_parse *box, char *line, int i);
int				assert_room_existence(t_parse *box, char *room_name);
int				assert_correct_node(char *lst_node_name, char *target);
int				room_description(t_parse *box);
int				link_description(t_parse *box, t_list *head);
t_list			*init_data_structure(t_parse *box);
t_list			*create_list(void);
void			free_list(t_list **head);
void			free_parser(t_parse **box);
void			printlst(t_list *head);
void			errout(int fg, char *mess);
void			free_hashtable(t_parse **box);
int				comment_clean(t_parse *box, int com);
int				hashtable(t_parse *box, char *room, int i);
int				hash(t_parse *box, char *room, size_t len);

void	karp(t_stock *stock, t_list *begin);
void	first_link(t_stock *stock, t_paths *curr);
void	current_saturated(t_stock *stock, t_paths *curr);
void	node_saturated(t_stock *stock, t_paths *curr);
void	opti_path(t_stock *stock, t_list *begin);
void	opti_path_next(t_stock *stock, t_list *begin, t_paths *curr, int i);
void	check_turn(t_stock *stock, int i);
void	sort_int_tab(t_stock *stock, int i);
void	max_flow(t_stock *stock, t_list *begin);
int		get_flow(t_stock *stock, t_list *begin, t_paths *curr);
t_wait	*add_list(t_stock *stock, t_list *elem, t_wait *list, int io);
t_list	*get_first_elem(t_stock *stock, t_wait *list);
t_wait  *check_add(t_stock *stock, t_list *begin, t_paths *curr, t_wait *list);
t_wait	*dispatch(t_stock *stock, t_list *begin, t_paths *curr, t_wait *list);
void    change_io(t_stock *stock);
char	check_sat(t_stock *stock, int a, int b);
void    init(t_stock *stock, t_list *begin);
void    remove_flow(t_stock *stock);
void	check_turn_next(t_stock *stock, int fourmi, int i, int j);
t_wait	*add_list_next(t_wait *begin, t_wait *list, t_wait *box);
void    init_get_flow(t_stock *stock, t_list *begin);
void	get_abp_next(t_stock *stock, int fourmi);
void	get_abp(t_stock *stock);
void	change_positions(t_stock *stock, t_list *curr, t_list *begin, t_list *prev);
void	sort_list(t_stock *stock, t_list *begin);
void	cut_paths(t_stock *stock, t_list *begin);
void	prepare_path(t_stock *stock, t_list *begin, t_list *path, int i);
void	get_in_line(t_stock *stock, t_list *begin);
void	reverse_paths(t_list *begin);
void	aff(t_stock *stock);
void	set_to(t_list *path);
void	aff_next(t_stock *stock, t_list *begin, t_list *path);
void	set_start(t_stock *stock, t_list *prev);
void	free_wait(t_stock *stock);
void	free_all(t_stock *stock);
void	error(t_stock *stock);
int		direct_path(t_list *begin, t_stock *stock);
void	print_direct_path(t_list *begin, t_paths *curr);
void    add_another_path(t_list *begin, t_paths *curr);
#endif
