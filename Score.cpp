#include "Score.h"
#include "NumberTexture.h"
#include "Assets.h"
#include <gslib.h>

// �R���X�g���N�^
Score::Score(int score) :
    score_{ score } {
}

// �X�R�A�̏�����
void Score::initialize(int score) {
    score_ = score;
}

// �X�R�A�̉��Z
void Score::add(int score) {
    score_ = MIN(score_ + score, 999);
}

// �X�R�A�̕`��
void Score::draw() const {
    // �u���_�v�̕\��
    static const GSrect rect{ 0, 64, 128, 128 };
    static const GSvector2 position{ 340, 20 };
    gsDrawSprite2D(Texture_Text, &position, &rect, NULL, NULL, NULL, 0.0f);
    // ���l�̕\��
    static const NumberTexture number{ Texture_Number, 32, 64 };
    number.draw(GSvector2{ 480, 20 }, score_, 3);
}

// �X�R�A�̎擾
int Score::get() const {
    return score_;
}

// �X�R�A�̃N���A
void Score::clear() {
    score_ = 0;
}

