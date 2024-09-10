/**
 * MIT License
 *
 * Copyright (c) 2024 HuaTsai
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include <polar_grid_rviz_plugins/polar_grid.hpp>

namespace polar_grid_rviz_plugins {

PolarGrid::PolarGrid(Ogre::SceneManager *scene_manager)
    : rviz_rendering::Object(scene_manager) {
  scene_node_ = std::shared_ptr<Ogre::SceneNode>(
      scene_manager_->getRootSceneNode()->createChildSceneNode());

  // Create concentric circles
  polars_.clear();
  for (int i = 0; i < 3; ++i) {
    std::shared_ptr<Ogre::ManualObject> obj(
        scene_manager_->createManualObject());
    obj->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
    float radius = 2 + i * 2;
    for (int j = 0; j <= 180; ++j) {
      float angle = Ogre::Math::TWO_PI * j / 180;
      float x = radius * Ogre::Math::Cos(angle);
      float y = radius * Ogre::Math::Sin(angle);
      obj->position(x, y, 0);
    }
    obj->end();
    scene_node_->attachObject(obj.get());
    polars_.push_back(obj);
  }
}

void PolarGrid::setPosition(const Ogre::Vector3 &position) {
  scene_node_->setPosition(position);
}

void PolarGrid::setOrientation(const Ogre::Quaternion &orientation) {
  scene_node_->setOrientation(orientation);
}

void PolarGrid::setScale(const Ogre::Vector3 &scale) { (void)scale; }

void PolarGrid::setColor(float r, float g, float b, float a) {
  (void)r;
  (void)g;
  (void)b;
  (void)a;
}

const Ogre::Vector3 &PolarGrid::getPosition() {
  return scene_node_->getPosition();
}

const Ogre::Quaternion &PolarGrid::getOrientation() {
  return scene_node_->getOrientation();
}

void PolarGrid::setUserData(const Ogre::Any &data) { (void)data; }

}  // namespace polar_grid_rviz_plugins
