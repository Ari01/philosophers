/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:57:11 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/16 13:34:19 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*ft_lstnew(int value)
{
	t_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **head, t_list *new)
{
	t_list	*ite;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		ite = *head;
		while (ite->next)
			ite = ite->next;
		ite->next = new;
	}
}

int	ft_lstfind(t_list *list, int value)
{
	while (list)
	{
		if (list->value == value)
			return (1);
		list = list->next;
	}
	return (0);
}

void	ft_lstremove(t_list **list, int to_remove)
{
	t_list	*ite;
	t_list	*tmp;

	if ((*list)->value == to_remove)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	else
	{
		ite = *list;
		while (ite->next->value != to_remove)
			ite = ite->next;
		tmp = ite->next;
		ite->next = ite->next->next;
		free(tmp);
	}
}
