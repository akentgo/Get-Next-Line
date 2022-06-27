/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:01:24 by akent-go          #+#    #+#             */
/*   Updated: 2022/05/13 11:34:47 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_clean_memory(char **mem)
{
	char	*new_mem;
	int		len;
	int		new_size;

	if (*mem == NULL)
	{
		*mem = (char *)malloc(sizeof(char));
		**mem = '\0';
		return ;
	}
	len = ft_line_len(*mem);
	new_size = ft_strlen(&(*mem)[len]) + 1;
	new_mem = (char *)malloc(sizeof(char) * new_size);
	ft_memcpy(new_mem, &(*mem)[len], new_size);
	free(*mem);
	*mem = new_mem;
}

int	ft_fill_memory(char **mem, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_check;
	char	*temp;

	ft_clean_memory(mem);
	read_check = 1;
	while (!ft_strchr(*mem, '\n') && read_check)
	{
		read_check = read(fd, buffer, BUFFER_SIZE);
		if (read_check < 1)
			return (read_check);
		buffer[read_check] = '\0';
		temp = *mem;
		*mem = ft_strjoin(*mem, buffer);
		free(temp);
	}
	return (read_check);
}

char	*ft_get_line(char **mem)
{
	char	*line;
	int		len;
	int		counter;

	len = ft_line_len(*mem);
	if (len == 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (len + 1));
	counter = 0;
	while (counter < len)
	{
		line[counter] = (*mem)[counter];
		counter++;
	}
	line[counter] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*mem[256] = {0};
	char			*line;

	if (fd < 0 || fd > 255)
		return (NULL);
	if (ft_fill_memory(&mem[fd], fd) == -1)
	{
		free(mem[fd]);
		mem[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(&mem[fd]);
	if (!line)
	{
		free(mem[fd]);
		mem[fd] = NULL;
	}
	return (line);
}
