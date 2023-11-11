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

struct Mat4x4 get_proj_matrix(const float near, 
							  const float far, 
							  const float fov, 
							  const float aspect_ratio);

void matrix_vec3_mul(struct Mat4x4 mat, struct Vec4 *v);

void vector_mul(struct Vec4 *v1, float scalar);
void vector_div(struct Vec4 *v1, float divisor);

void vector_add(struct Vec4 *v1, struct Vec4 v2);

#endif
