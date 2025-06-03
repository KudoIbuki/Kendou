#include "GamePlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Light.h"
#include "CameraTPS.h"
#include "Assets.h"
#include "Enemy.h"
#include "EnemyGenerator.h"

// 開始
void GamePlayScene::start() {
    // 剣道部長メッシュの読み込み
    gsLoadSkinMesh(Mesh_Player, "Assets/model/Kendo/kendo.mshb");
   // 空手部長メッシュの読み込み
    gsLoadSkinMesh(Mesh_Enemy, "Assets/model/Karate/karate.mshb");

    // スカイボックス用テクスチャの読み込み
    gsLoadTexture(Texture_Skybox, "Assets/texture/skybox.dds");
    // 数値用テクスチャの読み込み
    gsLoadTexture(Texture_Number, "Assets/texture/num.png");
    // 文字用テクスチャの読み込み
    gsLoadTexture(Texture_Text, "Assets/texture/text.png");

    // 校庭オクトリーの読み込み
    gsLoadOctree(Octree_Koutei, "Assets/model/Koutei/koutei.oct");
    // 校庭衝突判定用オクトリーの読み込み
    gsLoadOctree(Octree_KouteiCollider, "Assets/model/Koutei/koutei_collider.oct");

    // フィールドクラスの追加
    world_.add_field(new Field{ Octree_Koutei, Octree_KouteiCollider, Texture_Skybox });
    // カメラクラスの追加
    world_.add_camera(new CameraTPS{
              &world_, GSvector3{ 0.0f, 2.0f, -4.0f }, GSvector3{ 0.0f, 1.0f, 0.0f } });
    // ライトクラスの追加
    world_.add_light(new Light{ &world_ });
    // プレーヤーを追加
    world_.add_actor(new Player{ &world_, GSvector3{ 0.0f, 0.0f, 0.0f } });
    // 敵生成クラスを追加
    world_.add_actor(new EnemyGenerator{ &world_ });
	// スコアの初期化
	world_.add_score(0);
}

// 更新
void GamePlayScene::update(float delta_time) {
    // テスト用にZキーを押したら敵を生成するようにする
    if (gsGetKeyTrigger(GKEY_Z)) {
        world_.add_actor(new Enemy{ &world_, GSvector3{0.0f, 0.0f, 20.0f} });
    }
    // ワールドの更新
    world_.update(delta_time);

}

// 描画
void GamePlayScene::draw() const {
    world_.draw();

}

// 終了しているか？
bool GamePlayScene::is_end() const {
    return false;
}

// 次のシーンを返す
std::string GamePlayScene::next() const {
    return "TitleScene";
}

// 終了
void GamePlayScene::end() {
    // ワールドを消去
    world_.clear();
}

