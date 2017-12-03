#ifndef __LIST_H_
#define __LIST_H_

#include <pthread.h>

typedef struct list_elem {
	struct list_elem	*prev;
	struct list_elem	*next;
	void			*info;
} list_elem;

typedef struct thread_info_list {
	list_elem	*head;
	list_elem	*tail;
	pthread_mutex_t	lock;
} thread_info_list;

int list_size(thread_info_list *list);
int list_insert_head(thread_info_list *list, list_elem *new);
int list_insert_tail(thread_info_list *list, list_elem *new);
int list_remove(thread_info_list *list, list_elem *new);
void print_list(thread_info_list *list);
#endif /* __LIST_H_ */
