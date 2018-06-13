/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:02:14 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/13 19:25:52 by ozalisky         ###   ########.fr       */
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
	struct s_link	*links;
	struct s_room	*start;
	int				steps;
}					t_r;

typedef struct		s_link
{
//	t_r				*previous_room;
	struct s_link	*next_link;
	struct s_room	*room;

	int				connected;
}					t_l;

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

	t_l				*links;


	int				ants_flag;
	int				rooms_flag;
	int				links_flag;
	int				start_flag;
	int				end_flag;
}					t_db;
int					ft_islink(char *str);
void				ft_savelink(t_db *db);
int					ft_isroom(char *str);
void				ft_saveroom(t_db *db);
void				ft_check_rooms(t_db *db);
void				ft_check_links(t_db *db);
#endif
