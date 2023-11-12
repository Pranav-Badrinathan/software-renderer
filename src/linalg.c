#include "defs.h"
#include "linalg.h"
#include <math.h>
#include <stdio.h>

struct Vec4 vector_add(struct Vec4 *v1, struct Vec4 *v2) {
	return (struct Vec4) {
		v1->x + v2->x,
		v1->y + v2->y,
		v1->z + v2->z,
	};
}

struct Vec4 vector_sub(struct Vec4 *v1, struct Vec4 *v2) {
	return (struct Vec4) {
		v1->x + v2->x,
		v1->y + v2->y,
		v1->z + v2->z,
	};
}

struct Vec4 vector_mul(struct Vec4 *v1, float scalar) {
	return (struct Vec4) {
		v1->x * scalar,
		v1->y * scalar,
		v1->z * scalar,
	};
}

struct Vec4 vector_div(struct Vec4 *v1, float divisor) {
	return (struct Vec4) {
		v1->x / divisor,
		v1->y / divisor,
		v1->z / divisor,
	};
}

float vector_dot(struct Vec4 *v1, struct Vec4 *v2) {
	return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z + v2->z);
}

struct Vec4 vector_cross(struct Vec4 *u, struct Vec4 *v) {
	return (struct Vec4) {
		u->y * v->z - u->z * v->y,
		u->z * v->x - u->x * v->z,
		u->x * v->y - u->y * v->x,
	};
}

float vector_mag(struct Vec4 *v) {
	return sqrtf(vector_dot(v, v));
}

struct Vec4 vector_norm(struct Vec4 *v) {
	return vector_div(v, vector_mag(v));
}

// MATRIX STUFFS

struct Mat4x4 get_proj_matrix(const float near, 
							  const float far, 
							  const float fov, 
							  const float aspect_ratio) {

	// Initialize matrix to 0;
	struct Mat4x4 mat = {0};

	const float atan = 1.0f / tanf(fov * 0.5f / 180 * (float)M_PI);

	mat.v[0][0] = aspect_ratio * atan;
	mat.v[1][1] = atan;
	mat.v[2][2] = far / (far - near);
	mat.v[3][2] = (-far * near) / (far - near);
	mat.v[2][3] = 1.0f;
	mat.v[3][3] = 0.0f;

	return mat;
}

struct Vec4 matrix_vec3_mul(struct Mat4x4 *mat, struct Vec4 *v) {
	struct Vec4 point = {0};

	point.x = v->x * mat->v[0][0] + v->y * mat->v[1][0] + v->z * mat->v[2][0] + v->w * mat->v[3][0];
	point.y = v->x * mat->v[0][1] + v->y * mat->v[1][1] + v->z * mat->v[2][1] + v->w * mat->v[3][1];
	point.z = v->x * mat->v[0][2] + v->y * mat->v[1][2] + v->z * mat->v[2][2] + v->w * mat->v[3][2];
	point.w = v->x * mat->v[0][3] + v->y * mat->v[1][3] + v->z * mat->v[2][3] + v->w * mat->v[3][3];

	return point;
}
