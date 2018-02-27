/*
 * generate_points.c
 *
 *  Created on: 12 May 2014
 *      Author: lorenzo
 */

#include "time.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#define SCALAR(x, y) ((x)[0]*(y)[0] + (x)[1]*(y)[1] + (x)[2]*(y)[2])
#define SQR(x) ((x)*(x))
#define MATRIX_VECTOR_MULTIPLICATION(m, v, result) {\
	(result)[0] = (m)[0][0]*(v)[0] + (m)[0][1]*(v)[1] + (m)[0][2]*(v)[2];\
	(result)[1] = (m)[1][0]*(v)[0] + (m)[1][1]*(v)[1] + (m)[1][2]*(v)[2];\
	(result)[2] = (m)[2][0]*(v)[0] + (m)[2][1]*(v)[1] + (m)[2][2]*(v)[2];\
}


#define MAX_ROT 0.1
#define DEFAULT_STEPS 1000

typedef double vector[3];
typedef double matrix[3][3];

void get_rotation_matrix(vector axis, double t, matrix rotation_matrix) {
	double st = sin(t);
	double ct = cos(t);
	double uct = 1. - ct;

	rotation_matrix[0][0] = SQR(axis[0]) + (1. - SQR(axis[0]))*ct;
	rotation_matrix[0][1] = axis[0]*axis[1]*uct - axis[2]*st;
	rotation_matrix[0][2] = axis[0]*axis[2]*uct + axis[1]*st;

	rotation_matrix[1][0] = axis[0]*axis[1]*uct + axis[2]*st;
	rotation_matrix[1][1] = SQR(axis[1]) + (1. - SQR(axis[1]))*ct;
	rotation_matrix[1][2] = axis[1]*axis[2]*uct - axis[0]*st;

	rotation_matrix[2][0] = axis[0]*axis[2]*uct - axis[1]*st;
	rotation_matrix[2][1] = axis[1]*axis[2]*uct + axis[0]*st;
	rotation_matrix[2][2] = SQR(axis[2]) + (1. - SQR(axis[2]))*ct;
}

void get_rotated_vector(vector v, vector axis, double t, vector res) {
	matrix rotation_matrix;
	get_rotation_matrix(axis, t, rotation_matrix);
	MATRIX_VECTOR_MULTIPLICATION(rotation_matrix, v, res);
}

void rotate_vector(vector v, vector axis, double t) {
	vector tmp;
	get_rotated_vector(v, axis, t, tmp);
	v[0] = tmp[0];
	v[1] = tmp[1];
	v[2] = tmp[2];
}

void normalize(vector v) {
	double norm = sqrt(SCALAR(v, v));
	v[0] /= norm;
	v[1] /= norm;
	v[2] /= norm;
}

void random_vector_on_sphere(vector res) {
	double ransq;
	double ran1, ran2;
	double ranh;

	do {
		ran1 = 1. - 2.*drand48();
		ran2 = 1. - 2.*drand48();
		ransq = SQR(ran1) + SQR(ran2);
	} while(ransq >= 1.);

	ranh = 2.*sqrt(1. - ransq);

	res[0] = ran1*ranh;
	res[1] = ran2*ranh;
	res[2] = 1. - 2.*ransq;
}

double get_patch_energy(vector *points, int n_points, int p) {
	int i;
	double E = 0;

	for(i = 0; i < n_points; i++) {
		if(i != p) {
			vector r = {
					points[p][0] - points[i][0],
					points[p][1] - points[i][1],
					points[p][2] - points[i][2]
			};

			double r_mod = sqrt(SCALAR(r, r));
			E += 1. / r_mod;
		}
	}

	return E;
}

double tot_patch_energy(vector *points, int n_points) {
	double E = 0;
	int i;
	for(i = 0; i < n_points; i++) {
		E += get_patch_energy(points, n_points, i);
	}
	E /= 2;

	return E;
}

void move_random_patch(vector *points, int n_points) {
	int p = drand48() * n_points;
	double Ei = get_patch_energy(points, n_points, p);

	vector old_p = {points[p][0], points[p][1], points[p][2]};
	double theta = drand48() * MAX_ROT;
	vector axis;
	random_vector_on_sphere(axis);
	rotate_vector(points[p], axis, theta);

	double Ef = get_patch_energy(points, n_points, p);

	if(Ef > Ei) {
		points[p][0] = old_p[0];
		points[p][1] = old_p[1];
		points[p][2] = old_p[2];
	}
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		fprintf(stderr, "Usage is %s n_points\n", argv[0]);
		exit(1);
	}

	srand48(12345);

	int n_points = atoi(argv[1]);
	int steps = (argc > 2) ? atoi(argv[2]) : DEFAULT_STEPS;
	vector *points = malloc(sizeof(vector) * n_points);

	int i, j;
	for(i = 0; i < n_points; i++) {
		random_vector_on_sphere(points[i]);
		normalize(points[i]);
	}

	for(i = 0; i < steps; i++) {
		if(i % (steps/10) == 0) {
			double E = tot_patch_energy(points, n_points);
			fprintf(stderr, "%d %lf\n", i, E);
		}
		for(j = 0; j < n_points; j++) move_random_patch(points, n_points);
	}

	for(i = 0; i < n_points; i++) {
		fprintf(stdout, "%lf %lf %lf\n", points[i][0], points[i][1], points[i][2]);
	}

	free(points);

	return 0;
}
