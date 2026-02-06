#ifndef DATASET_H
#define DATASET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
	float x;
	float y;
} Dataset_item;

typedef struct {
	Dataset_item **items;
	size_t size;
	size_t capacity;
} Dataset;

Dataset *dataset_init();
void dataset_append(Dataset *ds, Dataset_item *item);
void dataset_print(Dataset *ds);
void dataset_read(Dataset *ds, char *dataset_path);
void split_dataset(Dataset *ds, Dataset *train, Dataset *test, int train_ratio);
void dataset_destroy(Dataset *ds);

#endif // !DATASET_H
