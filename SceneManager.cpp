#include "SceneManager.h"
#include "SceneNull.h"

static SceneNull scene_null;   // nullシーン（何もしないダミーシーン）

// コンストラクタ
SceneManager::SceneManager() :
    current_scene_{ &scene_null } {
}

// デストラクタ
SceneManager::~SceneManager() {
    clear();
}

// 更新
void SceneManager::update(float delta_time) {
    // シーンの更新
    current_scene_->update(delta_time);
    // シーンが終了しているか？
    if (current_scene_->is_end()) {
        // シーンを変更する
        change(current_scene_->next());
    }
}

// 描画
void SceneManager::draw() const {
    // 現在のシーンを描画
    current_scene_->draw();
}

// 終了
void SceneManager::end() {
    // 現在のシーンを終了
    current_scene_->end();
    // nullシーンにしておく
    current_scene_ = &scene_null;
}

// シーンの追加
void SceneManager::add(const std::string& name, IScene* scene) {
    scenes_[name] = scene;
}

// シーンの変更
void SceneManager::change(const std::string& name) {
    // 現在のシーンを終了
    end();
    // 現在のシーンを変更
    current_scene_ = scenes_[name];
    // 現在のシーンを開始
    current_scene_->start();
}


// シーンの消去
void SceneManager::clear() {
    // 念のためシーンの終了を呼び出す
    end();
    // unordered_map内のシーンをすべて削除
    for (auto& pair : scenes_) {
        delete pair.second; // シーンの削除
    }
    // unordered_mapを消去
    scenes_.clear();
}