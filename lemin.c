/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:02:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/20 15:41:32 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> //delete me
#include "lemin.h"

void	ft_check_line(t_db *db)
{
	if (db->ants < 1 && ft_isnumber(db->line) && !db->rooms_flag &&
	!db->links_flag)
	{
		db->ants = ft_atoi(db->line);
		db->moved_ants = db->ants;
		db->ants_flag = 1;
	}
	else if (ft_strcmp("##start", db->line) == 0 && db->start == -1)
	{
		ft_comments(db);
		db->start = 1;
	}
	else if (ft_strcmp("##end", db->line) == 0 && db->end == -1)
	{
		ft_comments(db);
		db->end = 1;
	}
	else
		ft_check_line_pt2(db);
	if (!db->error)
		ft_lineconcatmap(db);
	free(db->line);
	db->line = NULL;
}

void	ft_init(t_db *db)
{
	db->map = NULL;
	db->ants = 0;
	db->ants_flag = 0;
	db->start = -1;
	db->end = -1;
	db->error = 0;
	db->rooms = NULL;
	db->rooms_flag = 0;
	db->links_flag = 0;
	db->check_end = 0;
	db->steps = 0;
	db->ant_name_counter = 1;
	db->len = 0;
	db->cycle_start = 0;
}

char	*ft_str_cpy_ntrvl(t_db *db, size_t start, size_t end)
{
	char	*str;
	size_t	length;
	size_t	i;

	i = 0;
	length = end - start;
	str = ft_memalloc(sizeof(char) * (length + 1));
	while (start < end)
	{
		str[i++] = db->map[start++];
	}
	str[i] = '\0';
	return (str);
}

void	ft_find_links(t_db *db)
{
	db->lenlen = (size_t)ft_strlen(db->map);
	while (db->len <= db->lenlen)
	{
		db->line = NULL;
		if (db->map[db->len] == '\n' || db->map[db->len] == '\0')
		{
			db->line = ft_str_cpy_ntrvl(db, db->cycle_start, db->len);
			db->cycle_start = db->len + 1;
			if (ft_islink(db->line))
				ft_link_rooms(db);
		}
		if (db->line != NULL)
			free(db->line);
		db->line = NULL;
		if (db->map[db->len] == '\0')
			break ;
		++db->len;
	}
}

int		main(void)
{
	t_db	db;

	ft_init(&db);
	db.fd = open("../maps", O_RDONLY);
	/*db.fd = 0;*/
	while (!db.error && get_next_line(db.fd, &db.line) > 0)
	{
		if (db.line[0] == '\0')
		{
			ft_printf("ERROR\n");
			exit(0);
		}
		ft_check_line(&db);
	}
	free(db.line);
	close(db.fd);
	ft_validate(&db);
	ft_find_links(&db);
	ft_check_links(&db);
	search_ways((&db)->rooms->end, &db);
	ft_check_way(&db);
	ft_printf("%s\n\n", db.map);
	ft_ants(&db);
	exit(0);
}
