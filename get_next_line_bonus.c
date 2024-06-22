/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamarinh <tamarinh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 04:09:52 by tamarinh          #+#    #+#             */
/*   Updated: 2024/06/22 04:11:48 by tamarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_readed_line(char *fd_current)
{
	int		i;
	char	*line;

	if (fd_current[0] == 0)
		return (NULL);
	i = 0;
	while (fd_current[i] && fd_current[i] != '\n')
		i++;
	if (fd_current[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (fd_current[i] && fd_current[i] != '\n')
	{
		line[i] = fd_current[i];
		i++;
	}
	if (fd_current[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_move_start(char	*fd_start)
{
	char	*new_buff;
	int		i;
	int		j;

	i = 0;
	while (fd_start[i] && fd_start[i] != '\n')
		i++;
	if (fd_start[i] == '\0')
	{
		free(fd_start);
		return (NULL);
	}
	if (fd_start[i] == '\n')
		i++;
	new_buff = (char *)malloc((1 + ft_strlen(fd_start) - i) * (sizeof(char *)));
	if (!new_buff)
		return (NULL);
	j = -1;
	while (fd_start[i + j++])
		new_buff[j] = fd_start[i + j];
	new_buff[j] = '\0';
	free(fd_start);
	return (new_buff);
}

char	*ft_read_the_line(int fd, char *fd_str)
{
	int		n_bytes;
	char	*buff;

	n_bytes = 1;
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while ((ft_strchr(fd_str, '\n') == NULL) && n_bytes != 0)
	{
		n_bytes = read(fd, buff, BUFFER_SIZE);
		if (n_bytes == -1)
		{
			free(buff);
			free(fd_str);
			return (NULL);
		}
		buff[n_bytes] = '\0';
		fd_str = ft_strjoin(fd_str, buff);
	}
	free(buff);
	return (fd_str);
}

char	*get_next_line(int fd)
{
	static char	*fd_strs[1024] = {NULL};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_strs[fd] = ft_read_the_line(fd, fd_strs[fd]);
	if (fd_strs[fd] == NULL)
		return (NULL);
	line = ft_readed_line(fd_strs[fd]);
	fd_strs[fd] = ft_move_start(fd_strs[fd]);
	return (line);
}

// int main()
// {
// 	char *str;
// 	int fd;
// 	fd = open("some.txt", O_RDONLY);
// 	str = (char *)1;
// 	while(str != NULL)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s", str);
// 		free(str);	
// 	}
// 	return (0);
// }  
/*
int main()
{
	char *str1;
	char  *str2;
	char  *str3;
	int fd1; 
	int fd2;
	int fd3;
	
	fd1 = open("this.txt", O_RDONLY);
	fd2 = open("some.txt", O_RDONLY);
	fd3 = open("what.txt", O_RDONLY);
	
	str1 = (char *)1;
	str2 = (char *)1;
	str3 = (char *)1;
//	while(str1 != NULL || str2 != NULL || str3 != NULL)
//	{
//		str2 = get_next_line(fd2);
//		str3 = get_next_line(fd3);
//		printf("%s\n", str2);
//		printf("%s\n", str3);
//		free(str2);	
//		free(str3);
//	} 
	printf("------------------------------1\n");
	while (str1 != NULL)
	{
		str1 = get_next_line(fd1);
		printf("%s\n", str1);
		free(str1);
		printf("address -%p\n", str1);
	}
	printf("------------------------------2\n");
	while (str2 != NULL)
	{
		str2 = get_next_line(fd2);
		printf("%s\n", str2);
		free(str2);
	}
	printf("------------------------------3\n");
	while (str3 != NULL)
	{
		str3 = get_next_line(fd3);
		printf("%s\n", str3);
		free(str3);
	}	
	return (0);
}*/
