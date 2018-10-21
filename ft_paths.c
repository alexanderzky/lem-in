/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 18:15:39 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/21 16:07:43 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_rollback(t_r *tmpry, t_db *db)
{
	tmpry->connected = 0;
	if (db->steps)
		--db->steps;
}

int		ft_check_conditions(size_t i_links, t_r *tmpry, t_db *db)
{
	if (i_links < tmpry->links_size && (tmpry->links)[i_links] &&
	((!((tmpry->links)[i_links])->connected &&
	tmpry->links[i_links]->position == -1 &&
	tmpry->links[i_links]->step == 2147483647) ||
	(((tmpry->links)[i_links])->step >= db->steps + 1 &&
	tmpry->links[i_links]->position != 1 &&
	tmpry->links[i_links]->position != 0)))
		return (1);
	return (0);
}

void	search_ways(t_r *tmpry, t_db *db)
{
	size_t		i_links;

	if (tmpry->position)
	{
		++db->steps;
		tmpry->connected = 1;
		tmpry->step = db->steps;
	}
	if (tmpry->position == 1)
	{
		ft_rollback(tmpry, db);
		return ;
	}
	i_links = 0;
	while (i_links < tmpry->links_size)
	{
		while (ft_check_conditions(i_links, tmpry, db))
		{
			search_ways((tmpry->links)[i_links], db);
			++i_links;
		}
		++i_links;
	}
	ft_rollback(tmpry, db);
}
