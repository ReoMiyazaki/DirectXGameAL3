#include "Player/Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->textureHandle_ = textureHandle;

	// シングルインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() {
	Move();
};

void Player::Draw(ViewProjection viewProjection_) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

void Player::Move() {
	affin::AffinMat affinMat;

	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };
	// キャラクター移動の速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更
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

	// 制限限界座標
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 19.0f;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// スケーリング・回転・平行移動を合成した行列の計算
	affin::setTranslateMat(affinMat.translate, worldTransform_);
	worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	affin::setTransformationWolrdMat(affinMat, worldTransform_);

	// ワールド行列を転送
	worldTransform_.TransferMatrix();

	// デバッグ用表示
	debugText_->SetPos(50, 150);
	debugText_->Printf(
		"Root:(%f,%f,%f)", worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);
};