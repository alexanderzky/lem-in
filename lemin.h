/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:02:14 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/07 17:19:10 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef LEM_IN_LEMIN_H
#define LEM_IN_LEMIN_H
#include "./libft/libft.h"

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				position;
	struct s_room	*next_room;
	struct s_room	*start;
}					t_r;

typedef struct		s_link
{
	t_r			*previous_room;
	t_r			*next_room;

	int				position;
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

	t_r				rooms;

	t_l				links;
}					t_db;

#endif //LEM_IN_LEMIN_H
