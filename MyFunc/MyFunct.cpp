#include "MyFunc.h"
#include "affine/affin.h"

void MyFunc::Transform(WorldTransform& worldTransform, int i) {
	affin::AffinMat affinMat;
	// スケーリング・回転・平行移動を合成した行列の計算
	affin::setRotateMat(affinMat, worldTransform);
	affin::setTranslateMat(affinMat.translate, worldTransform);
	worldTransform.matWorld_ = MathUtility::Matrix4Identity();
	affin::setTransformationWolrdMat(affinMat, worldTransform);

	if (i != 0) {
		// ワールド行列を掛けて代入
		worldTransform.matWorld_ *= worldTransform.parent_->matWorld_;
	}
	// ワールド行列を転送
	worldTransform.TransferMatrix();
};