#include "defs.h"
#include "linalg.h"
#include <math.h>
#include <stdio.h>

// VECTOR OPERATIONS

struct Vec4 vector_add(struct Vec4 *v1, struct Vec4 *v2) {
	return (struct Vec4) {
		v1->x + v2->x,
		v1->y + v2->y,
		v1->z + v2->z,
	};
}

struct Vec4 vector_sub(struct Vec4 *v1, struct Vec4 *v2) {
	return (struct Vec4) {
		v1->x - v2->x,
		v1->y - v2->y,
		v1->z - v2->z,
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

// MATRIX OPERATIONS 

struct Vec4 matrix_vec3_mul(struct Mat4x4 *mat, struct Vec4 *v) {
	struct Vec4 point = {0};

	point.x = v->x * mat->v[0][0] + v->y * mat->v[1][0] + v->z * mat->v[2][0] + v->w * mat->v[3][0];
	point.y = v->x * mat->v[0][1] + v->y * mat->v[1][1] + v->z * mat->v[2][1] + v->w * mat->v[3][1];
	point.z = v->x * mat->v[0][2] + v->y * mat->v[1][2] + v->z * mat->v[2][2] + v->w * mat->v[3][2];
	point.w = v->x * mat->v[0][3] + v->y * mat->v[1][3] + v->z * mat->v[2][3] + v->w * mat->v[3][3];

	return point;
}

struct Mat4x4 matrix_transpose(struct Mat4x4 *mat) {
	struct Mat4x4 ret = {0};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret.v[j][i] = mat->v[i][j];
		}
	}

	return ret;
}

struct Mat4x4 matrix_matrix_mul(struct Mat4x4 mat1, struct Mat4x4 mat2) {
	struct Mat4x4 ret = {0};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				ret.v[i][j] += mat1.v[i][k] * mat2.v[k][j];
			}
		}
	}

	return ret;
}

// PREDEFINED MATRICIES

struct Mat4x4 get_identity_matrix(void) {
	struct Mat4x4 identity = {0};
	identity.v[0][0] = 1.0f;
	identity.v[1][1] = 1.0f;
	identity.v[2][2] = 1.0f;
	identity.v[3][3] = 1.0f;

	return identity;
}

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

struct Mat4x4 get_xrot_matrix(const float angle) {
	struct Mat4x4 mat = get_identity_matrix();
	mat.v[1][1] = cosf(angle);
	mat.v[2][2] = cosf(angle);
	mat.v[2][1] = -sinf(angle);
	mat.v[1][2] = sinf(angle);

	return mat;
}

struct Mat4x4 get_yrot_matrix(const float angle) {
	struct Mat4x4 mat = get_identity_matrix();
	mat.v[0][0] = cosf(angle);
	mat.v[2][2] = cosf(angle);
	mat.v[0][2] = -sinf(angle);
	mat.v[2][0] = sinf(angle);

	return mat;
}

struct Mat4x4 get_zrot_matrix(const float angle) {
	struct Mat4x4 mat = get_identity_matrix();
	mat.v[0][0] = cosf(angle);
	mat.v[1][1] = cosf(angle);
	mat.v[1][0] = -sinf(angle);
	mat.v[0][1] = sinf(angle);

	return mat;
}

struct Mat4x4 get_scale_matrix(const struct Vec4 *scale) {
	struct Mat4x4 mat = get_identity_matrix();

	mat.v[0][0] = scale->x;
	mat.v[1][1] = scale->y;
	mat.v[2][2] = scale->z;
	return mat;
}

struct Mat4x4 get_trans_matrix(const struct Vec4 *trans) {

	struct Mat4x4 mat = get_identity_matrix();

	mat.v[3][0] = trans->x;
	mat.v[3][1] = trans->y;
	mat.v[3][2] = trans->z;
	return mat;
}

struct Mat4x4 get_model_matrix(const struct Vec4 *rot, 
							   const struct Vec4 *trans, 
							   const struct Vec4 *scale) {
	struct Mat4x4 m_scale = get_scale_matrix(scale);
	struct Mat4x4 m_rot = 
		matrix_matrix_mul(
			matrix_matrix_mul(get_xrot_matrix(rot->x), get_yrot_matrix(rot->y)), 
			get_zrot_matrix(rot->z));
	struct Mat4x4 m_trans = get_trans_matrix(trans);

	
	return matrix_matrix_mul(matrix_matrix_mul(m_scale, m_rot), m_trans);
}
