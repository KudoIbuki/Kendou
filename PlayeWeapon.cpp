#include "PlayerWeapon.h"
#include "IWorld.h"
#include "Field.h"
#include "Line.h"

//コンストラクタ
PlayerWeapon::PlayerWeapon(IWorld* world, const GSvector3& position, const GSvector3& velocity)
{
	// ワールドの設定
	world_ = world;
	// タグ名の設定
	tag_ = "PlayerWeaponTag";
	// 名前の設定
	name_ = "PlayerWeapon";
	// 衝突判定球の設定
	collider_ = BoundingSphere{ 0.1f, GSvector3{0.0f, 0.0f, 0.0f} };
	// 座標の初期化
	transform_.position(position);
	// 速度の初期化
	velocity_ = velocity;
}

// 更新
void PlayerWeapon::update(float delta_time) {
    // 寿命が尽きたら死亡
    if (lifespan_timer_ <= 0.0f) {
        die();
        return;
    }
    // 寿命の更新
    lifespan_timer_ -= delta_time;
    // フィールドとの衝突判定
    Line line;
    line.start = transform_.position();
    line.end = transform_.position() + velocity_ * delta_time;
    GSvector3 intersect;
    if (world_->field()->collide(line, &intersect)) {
        // 交点の座標に補正
        transform_.position(intersect);
        
        return;
    }
    // 移動する（ワールド座標系基準）
    transform_.translate(velocity_ * delta_time, GStransform::Space::World);
}

// 描画
void PlayerWeapon::draw() const {
    // デバッグ表示
    collider().draw();
}

// 衝突リアクション
void PlayerWeapon::react(Actor& other) {
    // 衝突したら死亡
    die();
}



