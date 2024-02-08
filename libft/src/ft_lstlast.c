/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:40:05 by alfgarci          #+#    #+#             */
/*   Updated: 2023/12/16 18:35:33 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		printf("p: %p\n", lst);
		printf("pn: %p\n", lst->next);
		if (!lst->next)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (lst);
}
