#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "LC1A_22_PM";

struct Vector2 {
	float x;
	float y;
};

struct Ball {
	Vector2 position;
	float time;
	Vector2 StartPosition;
	Vector2 EndPosition;
	float result;
	int IsEasing;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Ball ball[4]{};

	for (int i = 0; i < 4; i++) {
		ball[i].position = { 50.0f,(i + 1) * 100.0f };
		ball[i].StartPosition = { 50.0f,i*100.0f};
		ball[i].EndPosition = { 1230.0f,i * 100.0f };

	}

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

		for (int i = 0; i < 4; i++) {
			if (keys[DIK_SPACE] && ball[i].IsEasing == 0) {
				ball[i].IsEasing = 1;
			}

			if (ball[i].IsEasing == 1) {
				if (ball[i].time < 1) {
					ball[i].time += 0.01f;
				}
				if (ball[i].time > 1) {
					ball[i].time = 1.0f;
				}

				if (i == 0) {
					ball[i].position.x = (1 - ball[i].time) * ball[i].StartPosition.x + ball[i].time * ball[i].EndPosition.x;
				}
				if (i == 1) {
					ball[i].result = -(cosf(float(M_PI) * ball[i].time) - 1) / 2;
					ball[i].position.x = (1 - ball[i].result) * ball[i].StartPosition.x + ball[i].result * ball[i].EndPosition.x;
				}
				if (i ==2) {
					ball[i].result = 1 - (1 - ball[i].time) * (1 - ball[i].time);
					ball[i].position.x = (1 - ball[i].result) * ball[i].StartPosition.x + ball[i].result * ball[i].EndPosition.x;
				}
			}

		}

		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int i = 0; i < 4; i++) {
			Novice::DrawEllipse((int)ball[i].position.x, (int)ball[i].position.y, 50, 50, 0.0f, RED, kFillModeSolid);
		}

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
