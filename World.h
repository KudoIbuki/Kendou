#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "ActorManager.h"
#include "Score.h"

// ワールドクラス
class World : public IWorld {
public:
    // コンストラクタ
    World() = default;
    // デストラクタ
    ~World();
    // 更新
    void update(float delta_time);
    // 描画
    void draw() const;
    // 消去
    void clear();
    // カメラの追加
    void add_camera(Actor* camera);
    // ライトの追加
    void add_light(Actor* light);
    // フィールドの追加
    void add_field(Field* field);

    // アクターを追加
    virtual void add_actor(Actor* actor) override;
    // アクターの検索
    virtual Actor* find_actor(const std::string& name) const override;
    // 指定したタグ名を持つアクターの検索
    virtual std::vector<Actor*> find_actor_with_tag(const std::string& tag) const override;
    // アクター数を返す
    virtual int count_actor() const override;
    // 指定したタグ名を持つアクター数を返す
    virtual int count_actor_with_tag(const std::string& tag) const override;
    // メッセージの送信
    virtual void send_message(const std::string& message, void* param = nullptr) override;

    // カメラの取得
    virtual Actor* camera() override;
    // ライトの取得
    virtual Actor* light() override;
    // フィールドの取得
    virtual Field* field() override;
    // スコアの加算
    virtual void add_score(int score) override;

    // コピー禁止
    World(const World& other) = delete;
    World& operator = (const World& other) = delete;

private:
    // アクターマネージャー
    ActorManager  actors_;
    // ライト
    Actor* light_{ nullptr };
    // カメラ
    Actor* camera_{ nullptr };
    // フィールド
    Field* field_{ nullptr };
    Score		score_;

};

#endif