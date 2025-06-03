#include "Enemy.h"
#include "IWorld.h"
#include "Field.h"
#include "Line.h"
#include "Assets.h"
#include "Score.h"
// �G�̃��[�V�����f�[�^
enum {
    MotionIdle = 0,  // �A�C�h��
    MotionRun = 1,  // ����
    MotionGuard = 10, // �K�[�h��
    MotionDamage = 12, // �_���[�W
    MotionDown = 14  // �_�E����
};

// �R���X�g���N�^
Enemy::Enemy(IWorld* world, const GSvector3& position) :
    mesh_{ Mesh_Enemy, MotionIdle, true },
    motion_{ MotionIdle },
    motion_loop_{ true },
    state_{ State::Spawn } {
    world_ = world;
    name_ = "Enemy";
    tag_ = "EnemyTag";
    collider_ = BoundingSphere{ 0.5f, GSvector3{0.0f, 0.8f, 0.0f} };
    transform_.position(position);
    mesh_.transform(transform_.localToWorldMatrix());
}

// �X�V
void Enemy::update(float delta_time) {
    // ��Ԃ̍X�V
    update_state(delta_time);
    // �n�ʂƂ̏Փ˔���
    collide_field();
    // ���[�V������ύX
    mesh_.change_motion(motion_, motion_loop_);
    // ���b�V�����X�V
    mesh_.update(delta_time);
    // �s���ݒ�
    mesh_.transform(transform_.localToWorldMatrix());
}

// �`��
void Enemy::draw() const {
    // �_�ŏ����i2�t���[�������ɕ\���j
    if ((int)blink_timer_ % 4 < 2) {
        mesh_.draw();
    }
    // �Փ˔���̕`��
    collider().draw();
}

// �Փˏ���
void Enemy::react(Actor& other) {
    // �v���[���^�O�̃A�N�^�[�ƏՓ˂����ꍇ�̓_���[�W���ɑJ��
    if (other.tag() == "PlayerTag") {
        enable_collider_ = false; // �_���[�W���͏Փ˔���𖳌��ɂ���
        change_state(State::Damage, MotionDamage, false);

        // AttackCollider�ɏՓ˂����ꍇ�́A���_�����Z
        if (other.name() == "AttackCollider") {
            world_->add_score(1);
        }
    }
}


// ��Ԃ̍X�V
void Enemy::update_state(float delta_time) {
    switch (state_) {
    case State::Spawn:  spawn(delta_time);  break;
    case State::Move:   move(delta_time);   break;
    case State::Damage: damage(delta_time); break;
    case State::Down:   down(delta_time);   break;
    case State::Leave:  leave(delta_time);  break;
    }
    // ��ԃ^�C�}�̍X�V
    state_timer_ += delta_time;
}

// ��Ԃ̕ύX
void Enemy::change_state(State state, GSuint motion, bool loop) {
    motion_ = motion;
    state_ = state;
    state_timer_ = 0.0f;
    motion_loop_ = loop;
}

// �o����
void Enemy::spawn(float delta_time) {
    // �_�Ń^�C�}���X�V
    blink_timer_ += delta_time;
    // �v���[���[������
    Actor* player = world_->find_actor("Player");
    // �v���[���[�����Ȃ���Ή������Ȃ�
    if (player == nullptr) return;
    // �v���[���[����������
    transform_.lookAt(player->transform().position());
    // �P�b�Ԍo�߂��Ă��瑖��n�߂�
    if (state_timer_ >= 60.0f) {
        blink_timer_ = 0.0f;
        change_state(State::Move, MotionRun);
    }
}

// �ړ���
void Enemy::move(float delta_time) {
    // �O�i����i���[�J�����W��j 
    transform_.translate(0.0f, 0.0f, 0.05f * delta_time);
    // �ړ����
    change_state(State::Move, MotionRun);
    // �O���E���h�̒[�܂ŗ����狎��
    if (transform_.position().x > 21.1f ||
        transform_.position().x < -21.1f ||
        transform_.position().z >  21.1f ||
        transform_.position().z < -21.1f) {
        change_state(State::Leave, MotionGuard);
    }
}

// �_���[�W��
void Enemy::damage(float delta_time) {
    // �A�j���[�V�����̏I���҂��ă_�E�����ɑJ��
    if (state_timer_ >= mesh_.motion_end_time()) {
        change_state(State::Down, MotionDown, false);
    }
}

// �_�E����
void Enemy::down(float delta_time) {
    // �_�Ń^�C�}���X�V
    blink_timer_ += delta_time;
    // 1�b�Ԍo�߂��Ă��玀�S����
    if (state_timer_ >= 60.0f) {
        die();
    }
}

// �ޏo��
void Enemy::leave(float delta_time) {
    // �_�Ń^�C�}�̍X�V
    blink_timer_ += delta_time;
    // 1�b�ԓ_�ł��Ă��玀�S����
    if (state_timer_ >= 60.0f) {
        die();
    }
}

// �t�B�[���h�Ƃ̏Փ˔���
void Enemy::collide_field() {
    // �����̃I�t�Z�b�g
    const float FootOffset{ 0.2f };
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




