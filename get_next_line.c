/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:32:19 by akent-go          #+#    #+#             */
/*   Updated: 2022/05/13 13:09:47 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	new_mem = (char *)malloc(new_size * sizeof(char));
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
	static char		*mem = NULL;
	char			*line;

	if (ft_fill_memory(&mem, fd) == -1)
	{
		free(mem);
		mem = NULL;
		return (NULL);
	}
	line = ft_get_line(&mem);
	if (!line)
	{
		free(mem);
		mem = NULL;
	}
	return (line);
}
