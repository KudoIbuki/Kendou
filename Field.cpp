#include "Field.h"
#include "Ray.h"
#include "Line.h"
#include "BoundingSphere.h"

// コンストラクタ
Field::Field(GSuint octree, GSuint collider, GSuint skybox) :
    octree_{ octree }, collider_{ collider }, skybox_{ skybox } {
}

// 更新
void Field::update(float delta_time) {}

// 描画
void Field::draw() const {
    // スカイボックスの描画
    gsDrawSkyboxCubemap(skybox_);
    // オクトリーの描画
    gsDrawOctree(octree_);
}

// 線分との衝突判定
bool Field::collide(const Line& line, GSvector3* intersect, GSplane* plane) const {
    return gsOctreeCollisionLine(
        gsGetOctree(collider_),
        &line.start, &line.end, intersect, plane) == GS_TRUE;
}

// レイとの衝突判定
bool Field::collide(const Ray& ray, float max_distance,
    GSvector3* intersect, GSplane* plane) const {
    Line line{
         ray.position,
         ray.position + (ray.direction.normalized() * max_distance) };
    return collide(line, intersect, plane);
}

// 球体との衝突判定
bool Field::collide(const BoundingSphere& sphere, GSvector3* center) const {
    return gsOctreeCollisionSphere(
        gsGetOctree(collider_),
        &sphere.center, sphere.radius, center) == GS_TRUE;
}
