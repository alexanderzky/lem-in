/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_links.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:29:14 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/20 19:32:47 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_check_links(t_db *db)
{
	if (db->end ^ 2 || db->start ^ 2)
	{
		ft_printf("ERROR\n");
		exit(0);
	}
	if (db->start < 1 || db->end < 1)
	{
		ft_printf("ERROR\n");
		exit(0);
	}
	if (db->rooms->start->links_size == 0 || !db->rooms->start->links ||
		db->rooms->end->links_size == 0 || !db->rooms->end->links)
	{
		ft_printf("ERROR\n");
		exit(0);
	}
}

int		ft_isroom(t_db *db, char *str)
{
	db->is_room_wrong = 0;
	db->is_room_coordinates = 0;
	db->is_room_name = 0;
	db->is_room_spaces = 0;
	db->is_room_i = 0;
	while (db->is_room_i < ft_strlen(str))
	{
		ft_room_cycle(db, str);
	}
	if (db->is_room_name == 1 && db->is_room_spaces == 2 &&
		db->is_room_coordinates == 2 && db->is_room_wrong == 0)
		return (1);
	return (0);
}
