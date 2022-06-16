#include "Player/Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULL�|�C���^�`�F�b�N
	assert(model);

	this->model_ = model;
	this->textureHandle_ = textureHandle;

	// �V���O���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();
}

void Player::Update() {
	Move();
};

void Player::Draw(ViewProjection viewProjection_) {
	// 3D���f���̕`��
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

void Player::Move() {
	affin::AffinMat affinMat;

	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };
	// �L�����N�^�[�ړ��̑���
	const float kCharacterSpeed = 0.2f;

	// �����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_LEFT)) {
		move.x = -kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move.x = kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y = kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_DOWN)) {
		move.y = -kCharacterSpeed;
	}

	worldTransform_.translation_ += move;

	// �������E���W
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 19.0f;

	// �͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// �X�P�[�����O�E��]�E���s�ړ������������s��̌v�Z
	affin::setTranslateMat(affinMat.translate, worldTransform_);
	worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	affin::setTransformationWolrdMat(affinMat, worldTransform_);

	// ���[���h�s���]��
	worldTransform_.TransferMatrix();

	// �f�o�b�O�p�\��
	debugText_->SetPos(50, 150);
	debugText_->Printf(
		"Root:(%f,%f,%f)", worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);
};