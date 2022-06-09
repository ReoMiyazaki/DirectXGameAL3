#include "Matrix4.h"
#include "WorldTransform.h"
#include "MathUtility.h"
#include "math.h"

#pragma once
namespace affine {

	void setScaleMat(Matrix4& mat, WorldTransform& worldTransform);
	void setRotMat(Matrix4& mat, WorldTransform& worldTransform, int axis);
	void setTransformMat(Matrix4& mat, WorldTransform& worldTransform);

	Matrix4 generatScaleMat(WorldTransform& worldTransform);
	Matrix4 generatRotMat(WorldTransform& worldTransform);
	Matrix4 generatTransformMat(WorldTransform& worldTransform);
}
