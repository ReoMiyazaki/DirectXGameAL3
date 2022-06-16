#pragma once
#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "ViewProjection.h"
#include "affine/affin.h"
#include "math.h"
#include <cassert>

class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name = "model" > モデル </param>
	/// <param name = "textureHamdle" > テクスチャハンドル </param>
	void Initialize(Model* model, uint32_t textureHandle);


	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <patam name = "viewProjection"> ビュープロジェクション (参照渡し) </patam>
	void Draw(ViewProjection viewProjection_);

	void Move();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint16_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

};

