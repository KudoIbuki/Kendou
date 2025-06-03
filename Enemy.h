#ifndef ENEMY_H_
#define ENEMY_H_

#include "Actor.h"
#include "AnimatedMesh.h"

// �G�N���X
class Enemy : public Actor {
public:
    //�G�̏��
    enum class State {
        Spawn,      // �o����
        Move,       // �ړ���
        Damage,     // �_���[�W��
        Down,       // �_�E����
        Leave       // ���Œ�
    };
    // �R���X�g���N�^
    Enemy(IWorld* world, const GSvector3& position);
    // �X�V
    virtual void update(float delta_time) override;
    //  �`��
    virtual void draw() const override;
    // �Փˏ���
    virtual void react(Actor& other) override;

private:
    // ��Ԃ̍X�V
    void update_state(float delta_time);
    // ��Ԃ̕ύX
    void change_state(State state, GSuint motion, bool loop = true);
    // �o��
    void spawn(float delta_time);
    // �ړ�
    void move(float delta_time);
    // �_���[�W
    void damage(float delta_time);
    // �_�E��
    void down(float delta_time);
    // �ޏo
    void leave(float delta_time);
    // �t�B�[���h�Ƃ̏Փ˔���
    void collide_field();

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
    // �_�Ń^�C�}
    float           blink_timer_{ 0.0f };
};

#endif

