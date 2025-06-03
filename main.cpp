#include <GSgame.h> // gslib::Game�ɕK�v
#include "SceneManager.h"
#include "GamePlayScene.h"

// �Q�[���N���X
class MyGame : public gslib::Game 
{
public:
    // �R���X�g���N�^
    MyGame() : gslib::Game{ 1024, 768 } {
    }
    // �J�n
    void start() override {
        //�^�C�g���V�[����ǉ�
        scene_manager_.add("GamePlayScene", new GamePlayScene());
		// �^�C�g���V�[�����J�n
        scene_manager_.change("GamePlayScene");
        gsLoadSkinMesh(0, "Assets/model/Kendo/kendo.mshb");
        // ��蕔�����b�V���̓ǂݍ���
        gsLoadSkinMesh(1, "Assets/model/Karate/karate.mshb");

    }
    // �X�V
    void update(float delta_time) override {
        scene_manager_.update(delta_time);
    }
    // �`��
    void draw() override {
        scene_manager_.draw();
    }
    // �I��
    void end() override {
        scene_manager_.end();
        scene_manager_.clear();
    }

private:
    // �V�[���}�l�[�W���[
    SceneManager scene_manager_;

};

// ���C���֐�
int main() {
    return MyGame().run();
}
