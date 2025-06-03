#pragma once
#ifndef PLAYER_BULLET_H_
#define PLAYER_BULLET_H_

#include "Actor.h"

// �v���[���[�̒e�N���X
class PlayerWeapon : public Actor {
public:
    // �R���X�g���N�^
    PlayerWeapon(IWorld* world, const GSvector3& position, const GSvector3& velocity);
    // �X�V
    virtual void update(float delta_time) override;
    // �`��
    virtual void draw() const override;
    // �Փ˃��A�N�V����
    virtual void react(Actor& other) override;

private:
    // ����
    float lifespan_timer_;
};

#endif