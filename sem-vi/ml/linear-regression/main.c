#include "dataset.h"
#include "model.h"

int main(int argc, char *argv[])
{
	Dataset *ds, *train, *test;
	LinearRegression model;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s /path/to/dataset\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *dataset_path = argv[1];
	ds = dataset_init();
	train = dataset_init();
	test = dataset_init();
	dataset_read(ds, dataset_path);
	split_dataset(ds, train, test, 70);
	model = lreg_statistic(train);
	printf("a, b = %f, %f\n", model.a, model.b);
	lreg_test(&model, test);
	lreg_save_json(&model, "./model.json");

	dataset_destroy(test);
	dataset_destroy(train);
	dataset_destroy(ds);
}

