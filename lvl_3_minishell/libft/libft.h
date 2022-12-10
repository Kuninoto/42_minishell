/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 01:35:12 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/10 20:02:42 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>

// LIBFT MANDATORY ------------------------------
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *ptr, int x, size_t n);
void		ft_bzero(void *ptr, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
void		*ft_memchr(const void *str, int c, size_t n);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t nitems, size_t size);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

// LINKED LISTS ---------------------------------

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// Creates a new node
t_list		*ft_lstnew(void *content);
// Adds a new node at the front of the linked list
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
// Returns a pointer to the last node of the linked list
t_list		*ft_lstlast(t_list *lst);

// Adds a new node at the back of the linked list
void		ft_lstadd_back(t_list **head, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// GET_NEXT_LINE ---------------------------------
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif 

// Returns a line, ending in newline read from the file descriptor passed as a parameter
char		*get_next_line(int fd);
bool		gnl_strchr(const char *str, int ch);

// FT_PRINTF --------------------------------------

// Wannabe printf
int			ft_printf(const char *__format, ...);
int			prt_str(char const *str);
int			prt_ptr(void *ptr_addr);
int			prt_int(int n);
int			prt_unsigned(unsigned int nbr);
int			prt_hexa(unsigned int nbr, bool upper_case);

// UTILS -------------------------------------------

// Appends to_append on to_free, creating a new string, and frees to_free 
char		*join_free(char *to_free, char *to_append);
// Returns s1+s2, creating a new string, and frees s2
char		*join_freev2(char *s1, char *s2);
// Prints error_msg, followed by a newline, to STDERR and exits the program on failure
void		handle_errors(char *error_msg);
// Frees all elements in matrix and matrix!
void		free_matrix(char **matrix);

#endif