#ifndef ENEMY_GENERATOR_H_
#define ENEMY_GENERATOR_H_

#include "Actor.h"

// �G�����N���X
class EnemyGenerator : public Actor {
public:
    // �R���X�g���N�^
    EnemyGenerator(IWorld* world);
    // �X�V
    virtual void update(float delta_time) override;

private:
    // �G�̐���
    void generate();

private:
    // �o���^�C�}�[
    float timer_{ 0.0f };
};

#endif

