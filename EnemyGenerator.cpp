#include "EnemyGenerator.h"
#include "IWorld.h"
#include "Enemy.h"

// �ő�o�����i20�̂܂Łj
const int EnemyMaxCount{ 20 };
// �o���Ԋu(0.5�b�����j
const float GenerateInterval{ 30.0f };

// �R���X�g���N�^
EnemyGenerator::EnemyGenerator(IWorld* world) {
    world_ = world;
    tag_ = "EnemyGeneratorTag";
    name_ = "EnemyGenerator";
    enable_collider_ = false;
}

// �X�V
void EnemyGenerator::update(float delta_time) {
    // ���݂̓G�̐����擾
    int enemy_count = world_->count_actor_with_tag("EnemyTag");
    // �G�̍ő������������΁H
    if (enemy_count < EnemyMaxCount) {
        timer_ += delta_time;
        // �������Ԃ𒴂������H
        if (GenerateInterval < timer_) {
            // �G�̐���
            generate();
            // �������Ԃ̃��Z�b�g
            timer_ = 0.0f;
        }
    }
}

// �G�̐���
void EnemyGenerator::generate() {
    // �O���E���h�̒[���烉���_���ɏo��
    GSvector3 position{ 0.0f,0.0f,0.0f };
    // 4�ӂ̂ǂ�����o�����邩�����_���Ō���
    switch (gsRand(0, 3)) {
    case 0: // ���̕�
        position.x = gsRandf(-21.0f, 21.0f);
        position.z = -21.0f;
        break;
    case 1: // �E�[�̕�
        position.x = 21.0f;
        position.z = gsRandf(-21.0f, 21.0f);
        break;
    case 2: // ��O�̕�
        position.x = gsRandf(-21.0f, 21.0f);
        position.z = 21.0f;
        break;
    case 3: // ���[�̕�
        position.x = -21.0f;
        position.z = gsRandf(-21.0f, 21.0f);
        break;
    }
    // �G�𐶐�����
    world_->add_actor(new Enemy{ world_, position });
}

