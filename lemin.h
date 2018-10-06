/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:02:14 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/06 17:07:22 by ozalisky         ###   ########.fr       */
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
	int				position;
	struct s_room	*next_room;
	struct s_room	*prev_room;
	struct s_room	**links;
	struct s_room	*start;
	struct s_room	*end;
	int				step;
	size_t			links_size;
	size_t			link_slot;
	int				connected;
}					t_r;

//typedef struct		s_link
//{
////	t_r				*previous_room;
//	struct s_link	*next_link;
//	struct s_link	*prev_link;
//	struct s_room	*next_room;
//	struct s_room	*prev_room;
//
//
//}					t_l;

typedef struct		s_db
{
	int				fd;//delete after all is done!
	char			*line;

	char			*map;

	int				ants;

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
//void		*ft_realloc(void *ptr, size_t newsize, size_t oldsize);
#endif
