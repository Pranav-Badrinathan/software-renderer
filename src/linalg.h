#ifndef SREND_LINALG_H_
#define SREND_LINALG_H_

struct Vec4 {
	float x;
	float y;
	float z;
	float w;
};

struct Mat4x4 {
	float v[4][4];
};

struct Mat4x4 get_proj_matrix(void);

struct Vec4 matrix_vec3_mul(struct Mat4x4 mat, struct Vec4 v);

struct Vec4 vector_mul(struct Vec4 v1, float scalar);
struct Vec4 vector_div(struct Vec4 v1, float divisor);

struct Vec4 vector_add(struct Vec4 v1, struct Vec4 v2);

#endif
