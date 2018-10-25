/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:02:14 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/23 20:33:41 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEMIN_H
# define LEM_IN_LEMIN_H
# include "./libft/libft.h"

struct s_link;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				position;
	int				step;
	int				connected;
	int				is_vaccant;
	size_t			ant_name;
	size_t			finished_ants;
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
	char			*line;

	char			*map;

	size_t			ants;
	size_t			moved_ants;

	int				start;
	int				end;
	int				error;
	t_r				*rooms;
	int				check_end;
	int				ants_flag;
	int				rooms_flag;
	int				links_flag;
	int				steps;
	size_t			ant_name_counter;
	size_t			len;
	size_t			cycle_start;
	size_t			lenlen;
	int				is_room_i;
	int				is_room_spaces;
	int				is_room_name;
	int				is_room_coordinates;
	int				is_room_wrong;
	char			*source_name;
	char			*target_name;
	int				links_i;
}					t_db;
int					ft_islink(char *str);
void				ft_count_room_mentions(t_db *db);
int					ft_isroom(t_db *db, char *str);
void				ft_saveroom(t_db *db);
void				ft_check_rooms(t_db *db);
void				ft_check_links(t_db *db);
void				ft_operate(t_db *db);
void				ft_link_rooms(t_db *db);
void				ft_ants(t_db *db);
void				ft_go(t_r *room, t_db *db);
void				search_ways(t_r *tmpry, t_db *db);
void				ft_check_links(t_db *db);
void				ft_check_rooms(t_db *db);
void				ft_link_start(t_db *db, t_r *start);
void				ft_link_end(t_db *db, t_r *end);
int					ft_chrinstr(const char *s, int c);
void				ft_room_cycle(t_db *db, char *str);
int					ft_isroom(t_db *db, char *str);
void				ft_validate(t_db *db);
void				ft_comments(t_db *db);
void				ft_check_way(t_db *db);
int					ft_isnumber(char *str);
char				*ft_strcpysrc(const char *src);
void				ft_free_map(t_db *db);
void				ft_lineconcatmap(t_db *db);
void				ft_check_line_pt2(t_db *db);
#endif
