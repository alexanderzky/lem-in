/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:02:14 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/08 19:36:44 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef LEM_IN_LEMIN_H
#define LEM_IN_LEMIN_H
#include "./libft/libft.h"


struct		s_link;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				position; //1 start, 0 end, -1 else
	int				step;
	int				connected;
	int 			is_vaccant;
	size_t 			ant_name;
	size_t 			finished_ants;
	size_t			links_size;
	size_t			link_slot;
	struct s_room	*next_room;
	struct s_room	*prev_room;
	struct s_room	**links;
	struct s_room	*start;
	struct s_room	*end;
}					t_r;

typedef struct		s_db
{
	int				fd;//delete after all is done!
	char			*line;

	char			*map;

	size_t			ants;
	size_t 			moved_ants;

	int				start;
	int				end;

	int				error;

	t_r				*rooms;

//	t_l				*links;

	int				check_end;
	int				ants_flag;
	int				rooms_flag;
	int				links_flag;

	int 			steps;
	int 			ant_name_counter;

//	int tempSize;
}					t_db;
int					ft_islink(char *str);
void				ft_count_room_mentions(t_db *db);
int					ft_isroom(char *str);
void				ft_saveroom(t_db *db);
void				ft_check_rooms(t_db *db);
void				ft_check_links(t_db *db);
void				ft_operate(t_db *db);
void				ft_link_rooms(t_db *db);
void				ft_ants(t_db *db);
void ft_go(t_r *room, t_db *db);
void			search_ways(t_r *tmpry, t_db *db);
//void		*ft_realloc(void *ptr, size_t newsize, size_t oldsize);
#endif
