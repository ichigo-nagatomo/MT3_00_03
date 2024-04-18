#include <Novice.h>
#include <assert.h>

struct Vec3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {
	float m[4][4];
};

Matrix4x4 MakeTranslateMatrix(const Vec3 &translate) {
	Matrix4x4 matrix;
	matrix.m[0][0] = 1;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[0][3] = 0;
	matrix.m[1][0] = 0;
	matrix.m[1][1] = 1;
	matrix.m[1][2] = 0;
	matrix.m[1][3] = 0;
	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = 1;
	matrix.m[2][3] = 0;
	matrix.m[3][0] = translate.x;
	matrix.m[3][1] = translate.y;
	matrix.m[3][2] = translate.z;
	matrix.m[3][3] = 1;

	return matrix;
}

Matrix4x4 MakeScaleMatrix(const Vec3 &scale) {
	Matrix4x4 matrix;
	matrix.m[0][0] = scale.x;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[0][3] = 0;
	matrix.m[1][0] = 0;
	matrix.m[1][1] = scale.y;
	matrix.m[1][2] = 0;
	matrix.m[1][3] = 0;
	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = scale.z;
	matrix.m[2][3] = 0;
	matrix.m[3][0] = 0;
	matrix.m[3][1] = 0;
	matrix.m[3][2] = 0;
	matrix.m[3][3] = 1;

	return matrix;
}

Vec3 Transform(const Vec3& vector, const Matrix4x4 &matrix) {
	Vec3 result;
	// 各成分を計算
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;


	return result;
}

//
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void VectorScreenPrintf(int x , int y , Vec3 vector) {
	Novice::ScreenPrintf(
		x * kColumnWidth , y * kRowHeight , "%.02f" , vector.x
	);
	Novice::ScreenPrintf(
		x + 1 * kColumnWidth , y * kRowHeight , "%.02f" , vector.y
	);
	Novice::ScreenPrintf(
		x + 2 * kColumnWidth , y * kRowHeight , "%.02f" , vector.z
	);
}

void MatrixScreenPrintf(int x , int y , Matrix4x4 matrix) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth , y + row * kRowHeight , "%.02f" , matrix.m[row][column]
			);
		}
	}
}


const char kWindowTitle[] = "LD2B_06_ナガトモイチゴ_MT3_00_03";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//宣言・初期化
	Vec3 translate {4.1f , 2.6f , 0.8f};
	Vec3 scale {1.5f , 5.2f , 7.3f};
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Vec3 point{2.3f , 3.8f , 1.4f};
	Matrix4x4 transformMatrix = {
		1.0f, 2.0f, 3.0f, 4.0f,
		3.0f, 1.0f, 1.0f, 2.0f,
		1.0f, 4.0f, 2.0f, 3.0f,
		2.0f, 2.0f, 1.0f, 3.0f
	};
	Vec3 transformed = Transform(point , transformMatrix);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0 , 0 , transformed);
		MatrixScreenPrintf(0 , kRowHeight * 2 , translateMatrix);
		MatrixScreenPrintf(0 , kRowHeight * 7 , scaleMatrix);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
