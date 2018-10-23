/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lines_fncts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:41:35 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/23 20:33:41 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_free_map(t_db *db)
{
	if (db->map != NULL)
	{
		free(db->map);
		db->map = NULL;
	}
}

void	ft_lineconcatmap(t_db *db)
{
	char	*str;
	long	size_map;
	long	size_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size_line = ft_strlen(db->line);
	size_map = ft_strlen(db->map);
	if (!(str = (char*)ft_memalloc(sizeof(char*) * (size_line + size_map + 1))))
		db->error = 1;
	while (db->map != NULL && db->map[i])
		str[j++] = db->map[i++];
	ft_free_map(db);
	if (size_map ^ 0)
		str[j++] = '\n';
	i = 0;
	while (db->line[i])
		str[j++] = db->line[i++];
	str[j] = '\0';
	db->map = ft_strcpysrc(str);
	free(str);
	str = NULL;
}

void	ft_check_line_pt2(t_db *db)
{
	if (ft_isroom(db, db->line) && db->ants_flag && !db->links_flag)
	{
		ft_saveroom(db);
		db->rooms_flag = 1;
	}
	else if (ft_islink(db->line) && db->ants_flag && db->rooms_flag)
	{
		ft_count_room_mentions(db);
		db->links_flag = 1;
	}
	else if (db->line[0] ^ '#' || !db->ants_flag || (!ft_strcmp("##start",
	db->line) && db->start > 0) || (!ft_strcmp("##end", db->line) &&
	db->end > 0) || (db->line[0] == '#' &&
	(db->start == 1 || db->end == 1)))
		db->error = 1;
}
