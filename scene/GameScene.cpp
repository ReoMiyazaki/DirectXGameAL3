#include "GameScene.h"
#include "AxisIndicator.h"
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

	// 範囲forで全てのワールドトランスフォームを順に処理する
	for (WorldTransform& worldTransform : worldTransforms_) {

		// ワールドトランスフォーム
		worldTransform.Initialize();
		Afin(worldTransform);
	}
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

	// クリップ距離変更処理
	{
		const float nearChangeSpeed = 0.005f;
		// 上下キーでニアクリップ距離を増減
		if (input_->PushKey(DIK_UP)) {
			viewProjection_.nearZ += nearChangeSpeed;
		}
		else if (input_->PushKey(DIK_DOWN)) {
			viewProjection_.nearZ -= nearChangeSpeed;
		}
		// 行列の再計算
		viewProjection_.UpdateMatrix();

		// デバッグ用表示
		debugText_->SetPos(50, 130);
		debugText_->Printf("nearZ:%f", viewProjection_.nearZ);
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
	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, viewProjection_, textureHandle_);
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

void GameScene::Afin(WorldTransform worldTransform_) {


	// 乱数シード生成器
	std::random_device seed_gen;;
	// メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engin(seed_gen());
	// 乱数範囲の設定
	std::uniform_real_distribution<float> rot(0, XM_PI);
	std::uniform_real_distribution<float> trans(-10, 10);

	// スケーリング行列の宣言
	Matrix4 matScale;
	// 各軸用回転行列を宣言
	Matrix4 matRotX, matRotY, matRotZ;
	// 平行移動行列を宣言
	Matrix4 matTrans;


#pragma region スケーリング

	// X, Y, Z方向の設定
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	// スケーリング行列を宣言
	matScale = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	// スケーリング倍率を行列に設定する
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
#pragma endregion

#pragma region ローテイション
	// X, Y, Z軸周りの回転角を設定
	worldTransform_.rotation_ = { rot(engin), rot(engin), rot(engin) };
	// Z軸回転行列を宣言
	matRotZ = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	// Z軸回転行列の各要素数を設定
	matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);

	// X軸回転行列を宣言
	matRotX = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	// X軸回転行列の各要素数を設定
	matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_.rotation_.x);

	// Y軸回転行列を宣言
	matRotY = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	// X軸回転行列の各要素数を設定
	matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_.rotation_.y);
#pragma endregion

#pragma region トランスレイション
	// X, Y, Z軸周りの平行移動を設定

	worldTransform_.translation_ = { trans(engin),trans(engin) ,trans(engin) };
	// 平行移動行列を宣言
	matTrans = MathUtility::Matrix4Identity();
	// 移動量を行列に設定
	matTrans = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;
#pragma endregion

	//単位行列を代入
	worldTransform_.matWorld_ = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	// 掛け算して代入
	worldTransform_.matWorld_ *= matScale;
	worldTransform_.matWorld_ *= matRotZ;
	worldTransform_.matWorld_ *= matRotX;
	worldTransform_.matWorld_ *= matRotY;
	worldTransform_.matWorld_ *= matTrans;

	// 行列の転送
	worldTransform_.TransferMatrix();
};


