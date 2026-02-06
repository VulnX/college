#include "dataset.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dataset *dataset_init()
{
	Dataset *ds;

	list_init(ds);
	return ds;
}

void dataset_print(Dataset *ds)
{
	for (int i = 0 ; i < ds->size ; i++) {
		printf("x = %f, y = %f\n", ds->items[i]->x, ds->items[i]->y);
	}
}

void dataset_read(Dataset *ds, char *dataset_path)
{
	FILE *fp;
	char line[0x100];
	Dataset_item *item;

	fp = fopen(dataset_path, "r");
	if (!fp) {
		fprintf(stderr, "failed to open dataset: %s\n", dataset_path);
		exit(EXIT_FAILURE);
	}
	while (fgets(line, sizeof(line), fp)) {
		item = malloc(sizeof(*item));
		if (!item) {
			fprintf(stderr, "failed to alloc mem for item\n");
			exit(EXIT_FAILURE);
		}
		sscanf(line, "%f,%f\n", &item->x, &item->y);
		list_append(ds, item);
	}

	fclose(fp);
}

void split_dataset(Dataset *ds, Dataset *train, Dataset *test, int train_ratio)
{
	int train_size;
	int curr;
	bool *train_set;
	Dataset_item *cloned;

	curr = 0;
	train_size = train_ratio * ds->size / 100;
	train_set = calloc(ds->size, sizeof(train_set));
	srand(time(NULL));
	for (int i = 0 ; i < train_size ; i++) {
		do {
			curr = rand() % ds->size;
		} while (train_set[curr]);
		cloned = malloc(sizeof(*cloned));
		if (!cloned) {
			fprintf(stderr, "failed to alloc mem for cloned row\n");
			exit(EXIT_FAILURE);
		}
		memcpy(cloned, ds->items[curr], sizeof(*cloned));
		list_append(train, cloned);
		train_set[curr] = true;
	}
	for (int i = 0 ; i < ds->size ; i++) {
		if (train_set[i])
			continue;
		cloned = malloc(sizeof(*cloned));
		if (!cloned) {
			fprintf(stderr, "failed to alloc mem for cloned row\n");
			exit(EXIT_FAILURE);
		}
		memcpy(cloned, ds->items[curr], sizeof(*cloned));
		list_append(test, cloned);
	}
	free(train_set);
	train_set = NULL;
}

void dataset_destroy(Dataset *ds)
{
	for (int i = 0 ; i < ds->size ; i++) {
		free(ds->items[i]);
		ds->items[i] = NULL;
	}
	list_del(ds);
}
