/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:05:44 by mlacombe          #+#    #+#             */
/*   Updated: 2019/01/10 14:44:03 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*line_creator(int fd, t_list **lines)
{
	t_list	*tmp;

	if (!lines)
		return (NULL);
	tmp = *lines;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	ft_lstadd(lines, tmp);
	return (tmp);
}

static int		reader(int fd, char **line)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		i;

	while ((i = read(fd, buff, BUFF_SIZE)))
	{
		buff[i] = '\0';
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buff)))
			return (-1);
		free(tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (i);
}

static int		ft_strcpyfromc(char **dst, char *src, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *dst;
	while (src[i] && src[i] != c)
		i++;
	if (!(*dst = ft_strndup(src, i)))
		return (0);
	return (i);
}

int				get_next_line(int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	static t_list	*lines;
	size_t			i;
	t_list			*lstline;

	if (fd < 0 || !line || read(fd, buff, 0) < 0 ||
			!(lstline = line_creator(fd, &lines)) || BUFF_SIZE <= 0 )
		return (-1);
	tmp = lstline->content;
	i = reader(fd, &tmp);
	lstline->content = tmp;
	if (!i && !*tmp)
		return (0);
	i = ft_strcpyfromc(line, lstline->content, '\n');
	tmp = lstline->content;
	if (tmp[i] != '\0')
	{
		lstline->content = ft_strdup(&((lstline->content)[i + 1]));
		free(tmp);
	}
	else
		tmp[0] = '\0';
	return (1);
}
