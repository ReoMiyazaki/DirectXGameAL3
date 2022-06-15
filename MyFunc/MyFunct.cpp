#include "MyFunc.h"
#include "affine/affin.h"

void MyFunc::Transform(WorldTransform& worldTransform, int i) {
	affin::AffinMat affinMat;
	// �X�P�[�����O�E��]�E���s�ړ������������s��̌v�Z
	affin::setRotateMat(affinMat, worldTransform);
	affin::setTranslateMat(affinMat.translate, worldTransform);
	worldTransform.matWorld_ = MathUtility::Matrix4Identity();
	affin::setTransformationWolrdMat(affinMat, worldTransform);

	if (i != 0) {
		// ���[���h�s����|���đ��
		worldTransform.matWorld_ *= worldTransform.parent_->matWorld_;
	}
	// ���[���h�s���]��
	worldTransform.TransferMatrix();
};