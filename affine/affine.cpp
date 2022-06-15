#include "affine.h"

void affine::setScaleMat(Matrix4& mat, WorldTransform& worldTransform) {

	// �X�P�[�����O�{�����s��ɐݒ肷��
	mat.m[0][0] = worldTransform.scale_.x;
	mat.m[1][1] = worldTransform.scale_.y;
	mat.m[2][2] = worldTransform.scale_.z;

}

Matrix4 affine::generatScaleMat(WorldTransform& worldTransform) {

	// �X�P�[�����O�s���錾
	Matrix4 matScale = MathUtility::Matrix4Identity();
	// �X�P�[�����O�{�����s��ɐݒ肷��
	matScale.m[0][0] = worldTransform.scale_.x;
	matScale.m[1][1] = worldTransform.scale_.y;
	matScale.m[2][2] = worldTransform.scale_.z;

	return matScale;

}
