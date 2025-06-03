#include "Player.h"
#include "IWorld.h"
#include "Field.h"
#include "Line.h"
#include "Assets.h"
#include "AttackCollider.h"

enum {                      // �v���[���[���[�V�����f�[�^
    MotionIdle = 0,    // �A�C�h��
    MotionRun = 1,    // ����
    MotionAttack = 17,   // �U��
    MotionDamage = 14,   // �_���[�W
    MotionGetUp = 16    // �N���オ��
};

// �R���X�g���N�^
Player::Player(IWorld* world, const GSvector3& position) :
    mesh_{ Mesh_Player, MotionIdle, true },
    motion_{ MotionIdle },
    motion_loop_{ true },
    state_{ State::Move } {
    world_ = world;
    name_ = "Player";
    tag_ = "PlayerTag";
    collider_ = BoundingSphere{ 0.5f, GSvector3{0.0f, 0.8f, 0.0f} };
    transform_.position(position);
    mesh_.transform(transform_.localToWorldMatrix());
}

// �X�V
void Player::update(float delta_time) {
    // ��Ԃ̍X�V
    update_state(delta_time);
    // �n�ʂƂ̏Փ˔��� 
    collide_field();
    // ���[�V�����̕ύX
    mesh_.change_motion(motion_, motion_loop_);
    // ���b�V���̍X�V
    mesh_.update(delta_time);
    // �ϊ��s��̐ݒ�
    mesh_.transform(transform_.localToWorldMatrix());
}

// �`��
void Player::draw() const {
    // ���b�V���̕`��
    mesh_.draw();
    // �Փ˔���̃f�o�b�O�\��
    collider().draw();
}

// �Փˏ���
void Player::react(Actor& other) {
    // �_���[�W���̓��A�N�V�������Ȃ�
    if (state_ == State::Damage) return;
    // �G�ƏՓ˂����ꍇ�̓_���[�W���ɑJ��
    if (other.tag() == "EnemyTag") {
        enable_collider_ = false; // �_���[�W���͏Փ˔���𖳌��ɂ���
        change_state(State::Damage, MotionDamage, false);
    }
}

// ��Ԃ̍X�V
void Player::update_state(float delta_time) {
    // ��Ԃɂ�镪��
    switch (state_) {
    case State::Move:   move(delta_time);   break;
    case State::Attack: attack(delta_time); break;
    case State::Damage: damage(delta_time); break;
    case State::GetUp:  get_up(delta_time); break;
    }
    // ��ԃ^�C�}�̍X�V
    state_timer_ += delta_time;
}

// ��Ԃ̕ύX
void Player::change_state(State state, GSuint motion, bool loop) {
    motion_ = motion;
    motion_loop_ = loop;
    state_ = state;
    state_timer_ = 0.0f;
}

// �ړ���
void Player::move(float delta_time) {
    // �X�y�[�X�L�[�ōU��
    if (gsGetKeyTrigger(GKEY_SPACE)) {
        // �����̑O���ɏՓ˔�����o��������
        generate_attack_collider();
        // �U�����ɑJ��
        change_state(State::Attack, MotionAttack, false);
        return;
    }
    // �������Ȃ���΃A�C�h�����
    GSuint motion = MotionIdle;
    // ���E�L�[�ł�������ɉ�]
    float yaw{ 0.0f };
    if (gsGetKeyState(GKEY_A))  yaw = 3.0f;
    if (gsGetKeyState(GKEY_D)) yaw = -3.0f;
    transform_.rotate(0.0f, yaw * delta_time, 0.0f);
    // ��L�[�őO�i
    float speed{ 0.0f };
    if (gsGetKeyState(GKEY_W)) {
        speed = 0.1f;
        motion = MotionRun;
    }
    change_state(State::Move, motion);
    // �O�i����(���[�J�����W��j
    transform_.translate(0.0f, 0.0f, speed * delta_time);
    // �O���E���h���ɃN�����v
    GSvector3 position = transform_.position();
    position.x = CLAMP(position.x, -20.0f, 20.0f);
    position.z = CLAMP(position.z, -20.0f, 20.0f);
    transform_.position(position);
}

// �U����
void Player::attack(float delta_time) {
    // �U���̃��[�V�������I��������ړ����ɑJ��
    if (state_timer_ >= mesh_.motion_end_time()) {
        // �U�����[�V�������I��������ړ����ɑJ��
        change_state(State::Move, MotionIdle);
    }
}

// �_���[�W��
void Player::damage(float delta_time) {
    if (state_timer_ >= mesh_.motion_end_time()) {
        // �_���[�W�����I��������N���オ��
        change_state(State::GetUp, MotionGetUp, false);
    }
}

// �N���オ�蒆
void Player::get_up(float delta_time) {
    // �N���オ�胂�[�V�������I��������A�C�h�����ɑJ��
    if (state_timer_ >= mesh_.motion_end_time()) {
        // �Փ˔����L���ɂ���
        enable_collider_ = true;
        // �A�C�h����ԂɑJ��
        change_state(State::Move, MotionIdle);
    }
}

// �t�B�[���h�Ƃ̏Փ˔���
void Player::collide_field() {
    // �����̃I�t�Z�b�g
    const float FootOffset{ 0.1f };
    // �n�ʂƂ̏Փ˔���i�����Ƃ̌�������j
    GSvector3 position = transform_.position();
    Line line;
    line.start = position + collider_.center;
    line.end = position + GSvector3{ 0.0f, -FootOffset, 0.0f };
    GSvector3 intersect;  // �n�ʂƂ̌�_
    if (world_->field()->collide(line, &intersect)) {
        // ���������_����y���W�̂ݕ␳����
        position.y = intersect.y;
        // ���W��ύX����
        transform_.position(position);
    }
}

// �U������𐶐�����
void Player::generate_attack_collider() {
    // �U��������o��������ꏊ�̋���
    const float AttackColliderDistance{ 1.5f };
    // �U������̔��a
    const float AttackColliderRadius{ 1.0f };
    // �U��������o���ꏊ�̍���
    const float AttackColliderHeight{ 1.0f };

    // �U�����肪�L���ɂȂ�܂ł̒x������
    const float AttackCollideDelay{ 0.0f };
    // �U������̎���
    const float AttackCollideLifeSpan{ 30.0f };

    // �Փ˔�����o����������W�����߂�i�O���̈ʒu�j
    GSvector3 position = transform_.position() + transform_.forward() * AttackColliderDistance;
    // �����̕␳�i��������̍����j
    position.y += AttackColliderHeight;
    // �Փ˔���p�̋����쐬
    BoundingSphere collider{ AttackColliderRadius, position };
    // �Փ˔�����o��������
    world_->add_actor(new AttackCollider{ world_, collider,
        "PlayerTag", "AttackCollider", tag_, AttackCollideLifeSpan, AttackCollideDelay });
}
