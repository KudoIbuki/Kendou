#ifndef PLAYER_H_
#define PLAYER_H_

#include "Actor.h"
#include "AnimatedMesh.h"

// �v���[���N���X
class Player : public Actor {
public:
    // ���
    enum class State {
        Move,       // �ړ���
        Attack,     // �U����
        Damage,     // �_���[�W��
        GetUp       // �N���オ�蒆
    };

public:
    // �R���X�g���N�^
    Player(IWorld* world, const GSvector3& position);
    // �X�V
    virtual void update(float delta_time) override;
    // �`��
    virtual void draw() const override;
    // �Փˏ���
    virtual void react(Actor& other) override;

private:
    // ��Ԃ̍X�V
    void update_state(float delta_time);
    // ��Ԃ̕ύX
    void change_state(State state, GSuint motion, bool loop = true);
    // �ړ���
    void move(float delta_time);
    // �U����
    void attack(float delta_time);
    // �_���[�W��
    void damage(float delta_time);
    // �N���オ�蒆
    void get_up(float delta_time);
    // �t�B�[���h�Ƃ̏Փ˔���
    void collide_field();
    // �U������𐶐�����
    void generate_attack_collider();

private:
    // �A�j���[�V�����t�����b�V��
    AnimatedMesh    mesh_;
    // ���[�V�����ԍ�
    GSuint          motion_;
    // ���[�V�����̃��[�v�t���O
    bool            motion_loop_;
    // ���
    State           state_;
    // ��ԃ^�C�}
    float           state_timer_{ 0.0f };
};

#endif

