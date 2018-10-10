/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 18:15:39 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/10 17:48:37 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_rollback(t_r *tmpry, t_db *db)
{
	tmpry->connected = 0;
	if(db->steps)
		--db->steps; //--g_steps;
}

void			search_ways(t_r *tmpry, t_db *db)
{
	int		i_links;

	if (tmpry->position)
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
		while ((tmpry->links)[i_links] && ((!((tmpry->links)[i_links])->connected &&
		tmpry->links[i_links]->position == -1 && tmpry->links[i_links]->step == 2147483647)
			|| (((tmpry->links)[i_links])->step >= db->steps + 1 && tmpry->links[i_links]->position != 1 &&
			tmpry->links[i_links]->position != 0)))
		{
			search_ways((tmpry->links)[i_links], db);
			++i_links;
		}

//		if (!((tmpry->links)[i_links]))
//			break ;
//		search_ways((tmpry->links)[i_links], db);
		++i_links;
	}
	ft_rollback(tmpry, db);

}

void	ft_operate(t_db *db)
{
//	t_r *temp;
//	int flag;
//	int go = 0;
//
//	flag = 1;
//	temp = db->rooms->end;

	search_ways(db->rooms->end, db);
}
