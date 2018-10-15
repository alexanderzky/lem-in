/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:02:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/10/15 18:26:52 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> //delete


#include "lemin.h"

void	ft_validate(t_db *db)
{
	if (db->ants < 1 || db->ants > 2147483647)
	{
		ft_printf("ERROR ants\n");
		exit(0);
	}
	else if (!db->rooms)
	{
		ft_printf("ERROR rooms\n");
		exit(0);
	}
	if (!db->rooms_flag || !db->links_flag || db->error)
	{
		ft_printf("ERROR rooms || links || error\n");
		exit(0);
	}
//	ft_check_links(db);
	ft_check_rooms(db);
}

void	ft_comments(t_db *db)
{
	if (ft_strcmp(db->line, "##start") == 0)
	{
		db->start = 1;
	}
	else if (ft_strcmp(db->line, "##end") == 0)
	{
		db->end = 1;
	}
}

void ft_check_way(t_db *db)
{
	t_r *temp;
	size_t index;

	index = 0;
	temp = db->rooms->start;
	while (index < temp->links_size)
	{
		if (temp->links[index]->step != 2147483647)
		{
			return ;
		}
		index++;
	}
	ft_printf("ERROR no way\n");
	exit(0);
}

int		ft_isnumber(char *str)
{
	int i;

	i = 0;
	if (ft_atoi(str) < 0 || ft_atoi(str) > 2147483647)
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			++i;
		}
		else
			return (0);

	}
	return (1);
}

char	*ft_strcpysrc(const char *src)
{
	int i;
	char *dst;

	dst = ft_memalloc(sizeof(char*) * (ft_strlen(src) + 1));
	i = 0;
	while (src[i] ^ '\0')
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
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
	{
		str[j++] = db->map[i++];
	}
	if (db->map != NULL)
	{
		free(db->map);
		db->map = NULL;
	}
	if (size_map ^ 0)
	{
		str[j++] = '\n';
	}
	i = 0;
	while (db->line[i])
	{
		str[j++] = db->line[i++];
	}
	str[j] = '\0';
	db->map = ft_strcpysrc(str);
	free(str);
	str = NULL;
}

void	ft_check_line(t_db *db)
{
	if (db->ants < 1 && ft_isnumber(db->line) && !db->rooms_flag && !db->links_flag)
	{
		db->ants = ft_atoi(db->line);
		db->moved_ants = db->ants;
		db->ants_flag = 1;
	}
	else if (ft_strcmp("##start",db->line) == 0 && db->start == -1)
	{
		ft_comments(db);
		db->start = 1;
	}
	else if (ft_strcmp("##end",db->line) == 0 && db->end == -1)
	{
		ft_comments(db);
		db->end = 1;
	}
	else if (ft_isroom(db->line) && db->ants_flag && !db->links_flag)
	{
		ft_saveroom(db);
		db->rooms_flag = 1;
	}
	else if (ft_islink(db->line) && db->ants_flag && db->rooms_flag)
	{
		ft_count_room_mentions(db);
		db->links_flag = 1;
	}
	else if (db->line[0] ^ '#' || (!ft_strcmp("##start",db->line) && db->start > 0) ||
			(!ft_strcmp("##end",db->line) && db->end > 0) ||
			(db->line[0] == '#' && db->line[1] ^ '#' && (db->start == 1 || db->end == 1)))
		db->error = 1;
	else
		db->error = 1;
	if (!db->error)
		ft_lineconcatmap(db);
	free(db->line);
	db->line = NULL;
}

void	ft_init(t_db *db)
{
	db->map = NULL;
	db->ants = 0;
	db->start = -1;
	db->end = -1;
	db->error = 0;
	db->rooms = NULL;
//	db->links = NULL;
	db->rooms_flag = 0;
	db->links_flag = 0;
	db->check_end = 0;
	db->steps = 0;
	db->ant_name_counter = 1;
	db->len = 0;
}


char *ft_str_cpy_ntrvl(t_db *db, size_t start, size_t end)
{
	char *str;
	size_t length;
	size_t i;

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

int		main(void)
{
	t_db	db;

	ft_init(&db);
//	db.fd = open("../maps", O_RDONLY);
	db.fd = 0;
	while (!db.error && get_next_line(db.fd, &db.line) > 0)
	{

		if (db.line[0] == '\0')
			break ;
		ft_check_line(&db);
	}
	free(db.line);
	close(db.fd);
	ft_validate(&db);

	size_t start;
	start = 0;
	size_t lenlen = (size_t)ft_strlen(db.map);
	while (db.len <= lenlen)
	{

		if (db.map[db.len] == '\n' || db.map[db.len] == '\0')
		{
			db.line = ft_str_cpy_ntrvl(&db, start, db.len);
			start = db.len + 1;
			if(ft_islink(db.line))
			{
				ft_link_rooms(&db);
			}
		}
		if (db.map[db.len] == '\0')
			break ;
		++db.len;
	}

	ft_check_links(&db);
	search_ways((&db)->rooms->end, &db);
	ft_check_way(&db);
	ft_printf("%s\n\n",db.map);
	ft_go((&db)->rooms->start, &db);
//	close(db.fd);
	exit(0);
}

