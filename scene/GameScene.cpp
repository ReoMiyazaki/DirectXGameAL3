#include "GameScene.h"
#include "AxisIndicator.h"
#include "MyFunc/MyFunc.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include <math.h>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();

	//// 範囲forで全てのワールドトランスフォームを順に処理する
	//for (WorldTransform& worldTransform : worldTransforms_) {
	//	// ワールドトランスフォーム
	//	worldTransform.Initialize();
	//	Afin(worldTransform);
	//}
#pragma region ビュー変換行列
	// カメラ視点座標を設定
	//viewProjection_.eye = { 0,0,-10 };
	// カメラ注視点座標を指定
	//viewProjection_.target = { 10,0,0 };
	// カメラ上方向ベクトルを指定(右上の45度指定)
	//viewProjection_.up = { 0.0f, 0.0f, 0.0f };
#pragma endregion

#pragma region 射影変換行列
//	// カメラの垂直方向視野角を設定
//	viewProjection_.fovAngleY = 10.0f * (XM_PI / 180);
//	// アスペクト比を設定
//	viewProjection_.aspectRatio = 1.0f;
#pragma endregion

	// キャラクターの大元
	worldTransforms_[PartId::kRoot].Initialize();
	// 脊椎
	worldTransforms_[PartId::kSpine].Initialize();
	worldTransforms_[PartId::kSpine].parent_ = &worldTransforms_[PartId::kRoot];
	worldTransforms_[PartId::kSpine].translation_ = { 0,4.5f,0 };
	// 上半身

	// 胸
	worldTransforms_[PartId::kChest].Initialize();
	worldTransforms_[PartId::kChest].parent_ = &worldTransforms_[PartId::kSpine];
	worldTransforms_[PartId::kChest].translation_ = { 0,0,0 };
	// 頭
	worldTransforms_[PartId::kHead].Initialize();
	worldTransforms_[PartId::kHead].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kHead].translation_ = { 0,4.5f,0 };
	// 左腕
	worldTransforms_[PartId::kArmL].Initialize();
	worldTransforms_[PartId::kArmL].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kArmL].translation_ = { 4.5f,0,0 };
	// 右腕
	worldTransforms_[PartId::kArmR].Initialize();
	worldTransforms_[PartId::kArmR].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kArmR].translation_ = { -4.5f,0,0 };
	// 下半身
	// 尻
	worldTransforms_[PartId::kHip].Initialize();
	worldTransforms_[PartId::kHip].parent_ = &worldTransforms_[PartId::kSpine];
	worldTransforms_[PartId::kHip].translation_ = { 0,-4.5f,0 };
	// 左足
	worldTransforms_[PartId::kLegL].Initialize();
	worldTransforms_[PartId::kLegL].parent_ = &worldTransforms_[PartId::kHip];
	worldTransforms_[PartId::kLegL].translation_ = { 4.5f,-4.5f,0 };
	// 右足
	worldTransforms_[PartId::kLegR].Initialize();
	worldTransforms_[PartId::kLegR].parent_ = &worldTransforms_[PartId::kHip];
	worldTransforms_[PartId::kLegR].translation_ = { -4.5f,-4.5f,0 };

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 960);

	// 軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを初期化する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

}

void GameScene::Update() {
	//debugCamera_->Update();

#pragma region ビュー変換行列
//	// 視点移動処理
//	{
//		// 視点移動ベクトル
//		Vector3 move = { 0.0f,0.0f,0.0f };
//		// 視点移動の速さ
//		const float kEyeSpeed = 0.2f;
//		// 押した方向でベクトルを変更
//		if (input_->PushKey(DIK_W)) {
//			move.z += kEyeSpeed;
//		}
//		else if (input_->PushKey(DIK_S)) {
//			move.z -= kEyeSpeed;
//		}
//		// 視点移動(ベクトルの加算)
//		viewProjection_.eye += move;
//		// 行列の再計算
//		viewProjection_.UpdateMatrix();
//		// デバッグ用表示
//		debugText_->SetPos(50, 50);
//		debugText_->Printf(
//			"eye:(%f,%f,%f)", viewProjection_.eye.x,
//			viewProjection_.eye.y, viewProjection_.eye.z);
//	}
//	{
//		// 視点移動ベクトル
//		Vector3 move = { 0.0f,0.0f,0.0f };
//		// 注視点移動ベクトル
//		const float kTargetSpeed = 0.2f;
//		// 押した方向で移動ベクトルを変更
//		if (input_->PushKey(DIK_LEFT)) {
//			move.x += kTargetSpeed;
//		}
//		else if (input_->PushKey(DIK_RIGHT)) {
//			move.x -= kTargetSpeed;
//		}
//		// 注視点移動(ベクトル加算)
//		viewProjection_.target += move;
//		// 行列の再計算
//		viewProjection_.UpdateMatrix();
//		// デバッグ用表示
//		debugText_->SetPos(50, 70);
//		debugText_->Printf(
//			"target:(%f,%f,%f)", viewProjection_.target.x,
//			viewProjection_.target.y, viewProjection_.target.z);
//	}
//	{
//		// 上方向の回転行列の速さ[ラジアン/frame]
//		const float kUpRotSpeed = 0.05f;
//		// 押した方向で移動ベクトルを変更
//		if (input_->PushKey(DIK_SPACE)) {
//			viewAngle += kUpRotSpeed;
//			// 2πを超えたら0に戻す
//			viewAngle = fmodf(viewAngle, PI * 2.0f);
//		}
//		// 上方向ベクトルを計算(半径1の円周上の座標)
//		viewProjection_.up = { cosf(viewAngle),sinf(viewAngle),0.0f };
//		// 行列の再計算
//		viewProjection_.UpdateMatrix();
//		// デバッグ用表示
//		debugText_->SetPos(50, 900);
//		debugText_->Printf(
//			"up:(%f,%f,%f)", viewProjection_.up.x,
//			viewProjection_.up.y, viewProjection_.up.z);
//	}

#pragma endregion

#pragma region 射影変換行列

//	// FoV変更処理
//	{
//		const float angleChangeSpeed = 0.05f;
//		// 上キーで視野角が広がる 下キーで視野角が狭まる
//		if (input_->PushKey(DIK_UP)) {
//			if (viewProjection_.fovAngleY < XM_PI) {
//				viewProjection_.fovAngleY += angleChangeSpeed;
//			}
//		}
//		else if (input_->PushKey(DIK_DOWN)) {
//			if (viewProjection_.fovAngleY > 0.05f) {
//				viewProjection_.fovAngleY -= angleChangeSpeed;
//			}
//		}
//		// 行列の再計算
//		viewProjection_.UpdateMatrix();
//
//		// デバッグ用表示
//		debugText_->SetPos(50, 110);
//		debugText_->Printf(
//			"fovAnglrY(Degree):%f",
//			(viewProjection_.fovAngleY) / (XM_PI / 180));
//	}

//	// クリップ距離変更処理
//	{
//		const float nearChangeSpeed = 0.005f;
//		// 上下キーでニアクリップ距離を増減
//		if (input_->PushKey(DIK_UP)) {
//			viewProjection_.nearZ += nearChangeSpeed;
//		}
//		else if (input_->PushKey(DIK_DOWN)) {
//			viewProjection_.nearZ -= nearChangeSpeed;
//		}
//		// 行列の再計算
//		viewProjection_.UpdateMatrix();
//
//		// デバッグ用表示
//		debugText_->SetPos(50, 130);
//		debugText_->Printf("nearZ:%f", viewProjection_.nearZ);
//	}
#pragma endregion

#pragma region 親子関係

	// キャラクター移動処理
	{
		// キャラクターの移動ベクトル
		Vector3 move = { 0,0,0 };
		// キャラクター移動の速さ
		const float kCharacterSpeed = 0.2f;

		// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_LEFT)) {
			move = { -kCharacterSpeed, 0, 0 };
		}
		else if (input_->PushKey(DIK_RIGHT)) {
			move = { kCharacterSpeed, 0, 0 };
		}

		// 回転処理
		const float kRotValue = 0.2f;
		// 上半身回転処理
		Vector3 rotChest = { 0,0,0 };
		// 押した方向で回転ベクトルを変更
		if (input_->PushKey(DIK_U)) {
			rotChest = { 0,-kRotValue,0 };
		}
		else if (input_->PushKey(DIK_I)) {
			rotChest = { 0,kRotValue,0 };
		}

		// 上半身回転処理
		Vector3 rotHip = { 0,0,0 };

		// 押した方向で回転ベクトルを変更
		if (input_->PushKey(DIK_J)) {
			rotHip = { 0,-kRotValue,0 };
		}
		else if (input_->PushKey(DIK_K)) {
			rotHip = { 0,kRotValue,0 };
		}

		// Rootの移動値増減
		worldTransforms_[PartId::kRoot].translation_ += move;
		// 上下半身の回転
		worldTransforms_[PartId::kChest].rotation_ += rotChest;
		worldTransforms_[PartId::kHip].rotation_ += rotHip;

		for (int i = 0; i < kNumPartId; i++) {
			MyFunc::Transform(worldTransforms_[i], i);
		}

		// デバッグ用表示
		debugText_->SetPos(50, 150);
		debugText_->Printf(
			"Root:(%f,%f,%f)", worldTransforms_[PartId::kRoot].translation_.x,
			worldTransforms_[PartId::kRoot].translation_.y,
			worldTransforms_[PartId::kRoot].translation_.z);
	}

#pragma endregion
}


void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 範囲forで全てのワールドトランスフォームを順に処理する

//	for (WorldTransform& worldTransform : worldTransforms_) {
//		model_->Draw(worldTransform, viewProjection_, textureHandle_);
//	}

	for (int i = 2; i < kNumPartId; i++) {
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}