/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 18:15:39 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/06 19:48:39 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//void	ft_mark(t_r *tmpr, t_db *db)
//{
//	struct s_link	*tmpl;
//
//	if (tmpr->position ^ -1 && tmpr->position ^ 1)
//		tmpr->connected = 1;
//	if ((tmpr->position ^ -1 && tmpr->position ^ 1) && (tmpr->step > db->steps || tmpr->step == 0))
//	{
//		tmpr->step = ++db->steps;
//
//	}
////	tmp = tmpr->links;
//	while (tmpr)
//	{
//		if (tmpr->links->prev_room && tmpr->links->prev_room->connected == 1)
//		{
//			if (tmpr->links->prev_room->step > 0)
//			{
//				if (tmpr->links->prev_link)
//				{
//					tmpl = tmpr->links->prev_link;
//					while (tmpl && tmpl->prev_room->connected != 0)
//					{
//						if (tmpl->prev_link)
//						{
//							tmpl = tmpl->prev_link;
//						}
//						else
//						{
//							ft_mark(tmpl->prev_room, db);
//							break ;
//						}
//					}
//					if (tmpl->prev_room->connected == 0)
//						ft_mark(tmpl->prev_room, db);
//				}
//			}
//			ft_mark(tmpr->links->prev_room, db);
//		}
//		if (/*!tmpr || !tmpr->links->prev_room || */tmpr->position == 1)
//		{
//			--db->steps;
////			ft_mark(tmpr->links.n, db);
//			while (tmpr->links->prev_room->connected != 1)
//			{
//
//			}
//			ft_mark(tmpr->end, db);
//		}
//		ft_mark(tmpr->links->prev_room, db);
//	}
//	tmpr->connected = 0;
//}

//int 	ft_mark(t_db *db, t_r *temp)
//{
//	while (temp)
//	{
//		if (temp->step == 0 || temp->step > db->steps + 1)
//		{
//			temp->step = db->steps + 1;
//			temp = temp->links->prev_room;
//		}
//	}
//
//	while (temp->links->prev_room && temp->links->prev_room->position ^ 1)
//	{
//		++db->steps;
//		temp = temp->links->prev_room;
//		if (temp->step == 0 || temp->step > db->steps)
//		{
//			temp->step = db->steps;
//			temp->connected = 1;
//
//		}
//	}
//}

static void		ft_rollback(t_r *tmpry, t_db *db)
{
	tmpry->connected = 0;
	--db->steps; //--g_steps;
}

void			search_ways(t_r *tmpry, t_db *db)
{
	int		i_links;

	if (tmpry->position != -1)
	{
		++db->steps; //		++g_steps;

		tmpry->connected = 1;
		tmpry->step = db->steps;
	}
	if (tmpry->position == 1)
	{
		ft_rollback(tmpry, db);
		return ;
	}
	i_links = 0;
	while (tmpry->links && (tmpry->links)[i_links])
	{
		while ((tmpry->links)[i_links] && (((tmpry->links)[i_links])->connected
			|| ((tmpry->links)[i_links])->step <= db->steps + 1))
			++i_links;
		if (!((tmpry->links)[i_links]))
			break ;
		search_ways((tmpry->links)[i_links], db);
		++i_links;
	}
	ft_rollback(tmpry, db);
}

void	ft_operate(t_db *db)
{
	t_r *temp;
	int flag;
	int go = 0;

	flag = 1;
	temp = db->rooms->end;

	search_ways(db->rooms->end, db);





//	while (flag)
//	{
//	ft_mark(temp, db);
//	}

}
