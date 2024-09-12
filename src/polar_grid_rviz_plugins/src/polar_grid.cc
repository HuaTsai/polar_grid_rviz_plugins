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
#include <rviz_common/logging.hpp>
#include <rviz_rendering/material_manager.hpp>

namespace polar_grid_rviz_plugins {

PolarGrid::PolarGrid(Ogre::SceneManager *scene_manager, Ogre::SceneNode *parent_node)
    : rviz_rendering::Object(scene_manager) {
  static int count = 0;
  std::string name = "PolarGrid" + std::to_string(count++);

  polar_grid_ = std::shared_ptr<Ogre::ManualObject>(
      scene_manager->createManualObject(name));

  if (!parent_node) {
    parent_node = scene_manager->getRootSceneNode();
  }

  scene_node_ = std::shared_ptr<Ogre::SceneNode>(
      parent_node->createChildSceneNode());
  scene_node_->attachObject(polar_grid_.get());

  material_ = rviz_rendering::MaterialManager::createMaterialWithNoLighting(
      name + "Material");
}

void PolarGrid::draw() {
  polar_grid_->clear();
  polar_grid_->begin(material_->getName(), Ogre::RenderOperation::OT_LINE_LIST,
                     "rviz_rendering");
  for (auto radius : {2, 4, 6, 8, 10}) {
    for (int j = -180; j <= 180; ++j) {
      for (int k = 0; k < 2; ++k) {
        float angle_rad = Ogre::Math::PI * (j + k) / 180.f;
        float x = radius * Ogre::Math::Cos(angle_rad);
        float y = radius * Ogre::Math::Sin(angle_rad);
        polar_grid_->position(x, y, 0);
        polar_grid_->colour(color_);
      }
    }
  }
  polar_grid_->end();

  // TODO: boarders
  // std::shared_ptr<Ogre::ManualObject>
  // b(scene_manager_->createManualObject()); b->begin("BaseWhiteNoLighting",
  // Ogre::RenderOperation::OT_LINE_LIST); for (auto angle : {-60, -40, -20, 0,
  // 20, 40, 60}) {
  //   b->position(0, 0, 0);
  //   float angle_rad = Ogre::Math::PI * angle / 180.f;
  //   float x = 150.f * Ogre::Math::Cos(angle_rad);
  //   float y = 150.f * Ogre::Math::Sin(angle_rad);
  //   b->colour(color_);
  //   b->position(x, y, 0);
  // }
  // b->end();
  // scene_node_->attachObject(b.get());
  // polars_.push_back(b);
}

void PolarGrid::setPosition(const Ogre::Vector3 &position) {
  scene_node_->setPosition(position);
}

void PolarGrid::setOrientation(const Ogre::Quaternion &orientation) {
  scene_node_->setOrientation(orientation);
}

void PolarGrid::setScale(const Ogre::Vector3 &scale) { (void)scale; }

void PolarGrid::setColor(float r, float g, float b, float a) {
  color_ = Ogre::ColourValue(r, g, b, a);
  rviz_rendering::MaterialManager::enableAlphaBlending(material_, color_.a);
  draw();
}

const Ogre::Vector3 &PolarGrid::getPosition() {
  return scene_node_->getPosition();
}

const Ogre::Quaternion &PolarGrid::getOrientation() {
  return scene_node_->getOrientation();
}

void PolarGrid::setUserData(const Ogre::Any &data) { (void)data; }

std::shared_ptr<Ogre::SceneNode> PolarGrid::getSceneNode() { return scene_node_; }

}  // namespace polar_grid_rviz_plugins
