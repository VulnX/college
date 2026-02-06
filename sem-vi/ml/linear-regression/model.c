#include <math.h>
#include <stdio.h>
#include "model.h"
#include "dataset.h"

LinearRegression lreg_statistic(Dataset *ds)
{
	double x, y, xy, x_sq, n;
	double a, b;
	Dataset_item *curr;
	LinearRegression model;

	n = ds->size;
	x = y = xy = x_sq = 0;
	for (int i = 0 ; i < n ; i++) {
		curr = ds->items[i];
		x += curr->x;
		y += curr->y;
		xy += curr->x * curr->y;
		x_sq = curr->x * curr->x;
	}
	a = (y * x_sq - y * xy) / (n * x_sq - x * x);
	b = (n * xy - x * y) / (n * x_sq - x * x);
	model.a = a;
	model.b = b;
	return model;
}

float lreg_predict(LinearRegression *model, float x)
{
	return model->a + model->b * x;
}

void lreg_test(LinearRegression *model, Dataset *test)
{
	float predicted, actual, error;
	double rms;
	Dataset_item *curr;
	int n;

	n = test->size;
	rms = 0.0f;
	for (int i = 0 ; i < n ; i++) {
		curr = test->items[i];
		actual = curr->y;
		predicted = lreg_predict(model, curr->x);
		error = pow(predicted - actual, 2.0);
		rms += error;
	}

	rms /= n;
	rms = sqrt(rms);
	printf("RMS Error = %f\n", rms);
}
