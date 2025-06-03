#include "GamePlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Light.h"
#include "CameraTPS.h"
#include "Assets.h"
#include "Enemy.h"
#include "EnemyGenerator.h"

// �J�n
void GamePlayScene::start() {
    // �����������b�V���̓ǂݍ���
    gsLoadSkinMesh(Mesh_Player, "Assets/model/Kendo/kendo.mshb");
   // ��蕔�����b�V���̓ǂݍ���
    gsLoadSkinMesh(Mesh_Enemy, "Assets/model/Karate/karate.mshb");

    // �X�J�C�{�b�N�X�p�e�N�X�`���̓ǂݍ���
    gsLoadTexture(Texture_Skybox, "Assets/texture/skybox.dds");
    // ���l�p�e�N�X�`���̓ǂݍ���
    gsLoadTexture(Texture_Number, "Assets/texture/num.png");
    // �����p�e�N�X�`���̓ǂݍ���
    gsLoadTexture(Texture_Text, "Assets/texture/text.png");

    // �Z��I�N�g���[�̓ǂݍ���
    gsLoadOctree(Octree_Koutei, "Assets/model/Koutei/koutei.oct");
    // �Z��Փ˔���p�I�N�g���[�̓ǂݍ���
    gsLoadOctree(Octree_KouteiCollider, "Assets/model/Koutei/koutei_collider.oct");

    // �t�B�[���h�N���X�̒ǉ�
    world_.add_field(new Field{ Octree_Koutei, Octree_KouteiCollider, Texture_Skybox });
    // �J�����N���X�̒ǉ�
    world_.add_camera(new CameraTPS{
              &world_, GSvector3{ 0.0f, 2.0f, -4.0f }, GSvector3{ 0.0f, 1.0f, 0.0f } });
    // ���C�g�N���X�̒ǉ�
    world_.add_light(new Light{ &world_ });
    // �v���[���[��ǉ�
    world_.add_actor(new Player{ &world_, GSvector3{ 0.0f, 0.0f, 0.0f } });
    // �G�����N���X��ǉ�
    world_.add_actor(new EnemyGenerator{ &world_ });
	// �X�R�A�̏�����
	world_.add_score(0);
}

// �X�V
void GamePlayScene::update(float delta_time) {
    // �e�X�g�p��Z�L�[����������G�𐶐�����悤�ɂ���
    if (gsGetKeyTrigger(GKEY_Z)) {
        world_.add_actor(new Enemy{ &world_, GSvector3{0.0f, 0.0f, 20.0f} });
    }
    // ���[���h�̍X�V
    world_.update(delta_time);

}

// �`��
void GamePlayScene::draw() const {
    world_.draw();

}

// �I�����Ă��邩�H
bool GamePlayScene::is_end() const {
    return false;
}

// ���̃V�[����Ԃ�
std::string GamePlayScene::next() const {
    return "TitleScene";
}

// �I��
void GamePlayScene::end() {
    // ���[���h������
    world_.clear();
}

