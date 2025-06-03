#include "PlayerWeapon.h"
#include "IWorld.h"
#include "Field.h"
#include "Line.h"

//�R���X�g���N�^
PlayerWeapon::PlayerWeapon(IWorld* world, const GSvector3& position, const GSvector3& velocity)
{
	// ���[���h�̐ݒ�
	world_ = world;
	// �^�O���̐ݒ�
	tag_ = "PlayerWeaponTag";
	// ���O�̐ݒ�
	name_ = "PlayerWeapon";
	// �Փ˔��苅�̐ݒ�
	collider_ = BoundingSphere{ 0.1f, GSvector3{0.0f, 0.0f, 0.0f} };
	// ���W�̏�����
	transform_.position(position);
	// ���x�̏�����
	velocity_ = velocity;
}

// �X�V
void PlayerWeapon::update(float delta_time) {
    // �������s�����玀�S
    if (lifespan_timer_ <= 0.0f) {
        die();
        return;
    }
    // �����̍X�V
    lifespan_timer_ -= delta_time;
    // �t�B�[���h�Ƃ̏Փ˔���
    Line line;
    line.start = transform_.position();
    line.end = transform_.position() + velocity_ * delta_time;
    GSvector3 intersect;
    if (world_->field()->collide(line, &intersect)) {
        // ��_�̍��W�ɕ␳
        transform_.position(intersect);
        
        return;
    }
    // �ړ�����i���[���h���W�n��j
    transform_.translate(velocity_ * delta_time, GStransform::Space::World);
}

// �`��
void PlayerWeapon::draw() const {
    // �f�o�b�O�\��
    collider().draw();
}

// �Փ˃��A�N�V����
void PlayerWeapon::react(Actor& other) {
    // �Փ˂����玀�S
    die();
}



