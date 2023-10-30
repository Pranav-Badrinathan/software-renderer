#ifndef SREND_LINALG_H_
#define SREND_LINALG_H_

struct Vec3 {
	float x;
	float y;
	float z;
};

struct Mat4x4 {
	float v[4][4];
};

struct Mat4x4 get_proj_matrix(void);

struct Vec3 matrix_vec3_mul(struct Mat4x4 mat, struct Vec3 v);

struct Vec3 vector_mul(struct Vec3 v1, float scalar);

struct Vec3 vector_add(struct Vec3 v1, struct Vec3 v2);

#endif
