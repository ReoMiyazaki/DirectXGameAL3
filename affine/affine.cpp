#include "affine.h"

void affine::setScaleMat(Matrix4& mat, WorldTransform& worldTransform) {

	// スケーリング倍率を行列に設定する
	mat.m[0][0] = worldTransform.scale_.x;
	mat.m[1][1] = worldTransform.scale_.y;
	mat.m[2][2] = worldTransform.scale_.z;

}

Matrix4 affine::generatScaleMat(WorldTransform& worldTransform) {

	// スケーリング行列を宣言
	Matrix4 matScale = MathUtility::Matrix4Identity();
	// スケーリング倍率を行列に設定する
	matScale.m[0][0] = worldTransform.scale_.x;
	matScale.m[1][1] = worldTransform.scale_.y;
	matScale.m[2][2] = worldTransform.scale_.z;

	return matScale;

}
