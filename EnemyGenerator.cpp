#include "EnemyGenerator.h"
#include "IWorld.h"
#include "Enemy.h"

// 最大出現数（20体まで）
const int EnemyMaxCount{ 20 };
// 出現間隔(0.5秒おき）
const float GenerateInterval{ 30.0f };

// コンストラクタ
EnemyGenerator::EnemyGenerator(IWorld* world) {
    world_ = world;
    tag_ = "EnemyGeneratorTag";
    name_ = "EnemyGenerator";
    enable_collider_ = false;
}

// 更新
void EnemyGenerator::update(float delta_time) {
    // 現在の敵の数を取得
    int enemy_count = world_->count_actor_with_tag("EnemyTag");
    // 敵の最大よりも小さければ？
    if (enemy_count < EnemyMaxCount) {
        timer_ += delta_time;
        // 生成時間を超えたか？
        if (GenerateInterval < timer_) {
            // 敵の生成
            generate();
            // 生成時間のリセット
            timer_ = 0.0f;
        }
    }
}

// 敵の生成
void EnemyGenerator::generate() {
    // グラウンドの端からランダムに出現
    GSvector3 position{ 0.0f,0.0f,0.0f };
    // 4つ辺のどこから出現するかランダムで決定
    switch (gsRand(0, 3)) {
    case 0: // 奥の辺
        position.x = gsRandf(-21.0f, 21.0f);
        position.z = -21.0f;
        break;
    case 1: // 右端の辺
        position.x = 21.0f;
        position.z = gsRandf(-21.0f, 21.0f);
        break;
    case 2: // 手前の辺
        position.x = gsRandf(-21.0f, 21.0f);
        position.z = 21.0f;
        break;
    case 3: // 左端の辺
        position.x = -21.0f;
        position.z = gsRandf(-21.0f, 21.0f);
        break;
    }
    // 敵を生成する
    world_->add_actor(new Enemy{ world_, position });
}

