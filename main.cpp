#include <GSgame.h> // gslib::Gameに必要
#include "SceneManager.h"
#include "GamePlayScene.h"

// ゲームクラス
class MyGame : public gslib::Game 
{
public:
    // コンストラクタ
    MyGame() : gslib::Game{ 1024, 768 } {
    }
    // 開始
    void start() override {
        //タイトルシーンを追加
        scene_manager_.add("GamePlayScene", new GamePlayScene());
		// タイトルシーンを開始
        scene_manager_.change("GamePlayScene");
        gsLoadSkinMesh(0, "Assets/model/Kendo/kendo.mshb");
        // 空手部長メッシュの読み込み
        gsLoadSkinMesh(1, "Assets/model/Karate/karate.mshb");

    }
    // 更新
    void update(float delta_time) override {
        scene_manager_.update(delta_time);
    }
    // 描画
    void draw() override {
        scene_manager_.draw();
    }
    // 終了
    void end() override {
        scene_manager_.end();
        scene_manager_.clear();
    }

private:
    // シーンマネージャー
    SceneManager scene_manager_;

};

// メイン関数
int main() {
    return MyGame().run();
}
