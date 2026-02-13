#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "dataset.h"

typedef struct {
	float a;
	float b;
} LinearRegression;

LinearRegression lreg_statistic(Dataset *ds);
float lreg_predict(LinearRegression *model, float x);
void lreg_test(LinearRegression *model, Dataset *test);
void lreg_save_json(LinearRegression *model, const char *path);

#endif // !MODEL_H
