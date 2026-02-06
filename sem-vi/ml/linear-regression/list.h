#ifndef LIST_H
#define LIST_H

#define list_init(list) \
	do { \
		list = malloc(sizeof(*list)); \
		if (!list) { \
			fprintf(stderr, "failed to alloc mem for dataset\n"); \
			exit(EXIT_FAILURE); \
		} \
		list->capacity = 0x100; \
		list->size = 0; \
		list->items = calloc(list->capacity, sizeof(*list->items)); \
		if (!list->items) { \
			fprintf(stderr, "failed to alloc mem for list->items\n"); \
			exit(EXIT_FAILURE); \
		} \
	} while (0)

#define list_append(list, item) \
	if (list->size >= list->capacity) { \
		list->capacity *= 2; \
		list->items = realloc(list->items, list->capacity * sizeof(*list->items)); \
		if (!list->items) { \
			fprintf(stderr, "failed to alloc mem for list->items\n"); \
			exit(EXIT_FAILURE); \
		} \
	} \
	list->items[list->size++] = item;

#define list_del(list) \
	free(list->items); \
	free(list); \
	list = NULL;

#endif // !LIST_H
