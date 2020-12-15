/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberry <aberry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:43:25 by aberry            #+#    #+#             */
/*   Updated: 2020/11/24 20:22:11 by aberry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_check_remainder(char **line, char **remainder, int fd)
{
	char	*tmp;

	if (remainder[fd])
	{
		if ((tmp = ft_strchr(remainder[fd], '\n')))
		{
			*tmp++ = '\0';
			*line = ft_strdup(remainder[fd]);
			ft_strlcpy(remainder[fd], tmp, ft_strlen(tmp) + 1);
		}
		else
		{
			*line = ft_strdup(remainder[fd]);
			free(remainder[fd]);
			remainder[fd] = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (BUFFER_SIZE);
}

int	get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*remainder[ARRAY_SIZE];
	int				op_buff;

	if (BUFFER_SIZE < 1 || !line || fd < 0)
		return (-1);
	op_buff = gnl_check_remainder(line, remainder, fd);
	while (!remainder[fd] && (op_buff = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[op_buff] = '\0';
		if ((remainder[fd] = ft_strchr(buff, '\n')))
		{
			*remainder[fd]++ = '\0';
			remainder[fd] = ft_strdup(remainder[fd]);
		}
		*line = ft_strjoin_gnl(*line, buff);
	}
	if (op_buff < BUFFER_SIZE && !remainder[fd] && op_buff != -1)
		return (0);
	if (op_buff == -1)
	{
		free(*line);
		return (-1);
	}
	return (1);
}
