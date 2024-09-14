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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <polar_grid_rviz_plugins/polar_grid.hpp>
#include <rviz_common/logging.hpp>
#include <rviz_rendering/material_manager.hpp>

namespace polar_grid_rviz_plugins {

PolarGrid::PolarGrid(Ogre::SceneManager *scene_manager, Ogre::SceneNode *parent_node)
    : rviz_rendering::Object(scene_manager) {
  static int count = 0;
  std::string name = "PolarGrid" + std::to_string(count++);

  polar_grid_ = std::shared_ptr<Ogre::ManualObject>(scene_manager->createManualObject(name));

  if (!parent_node) {
    parent_node = scene_manager->getRootSceneNode();
  }

  scene_node_ = std::shared_ptr<Ogre::SceneNode>(parent_node->createChildSceneNode());
  scene_node_->attachObject(polar_grid_.get());

  material_ = rviz_rendering::MaterialManager::createMaterialWithNoLighting(name + "Material");
}

void PolarGrid::draw() {
  polar_grid_->clear();
  polar_grid_->begin(material_->getName(), Ogre::RenderOperation::OT_LINE_LIST, "rviz_rendering");

  int start_angle = 0, end_angle = 0;
  if (sectors_) {
    if (invert_) {
      start_angle = max_angle_;
      end_angle = min_angle_ + 360;
    } else {
      start_angle = min_angle_;
      end_angle = max_angle_;
    }
  } else {
    start_angle = 0;
    end_angle = 360;
  }

  float max_radius = 0.f;
  for (int i = 0; i < circles_count_; ++i) {
    float radius = min_radius_ + (i + (min_radius_ < 1e-6 ? 1 : 0)) * radius_step_;
    if (i == circles_count_ - 1) max_radius = radius;
    // XXX: May have better way, the number of points should not be fixed
    for (int j = start_angle; j < end_angle; ++j) {
      for (int k = 0; k < 2; ++k) {
        float angle_rad = Ogre::Math::PI * (j + k) / 180.f;
        float x = radius * Ogre::Math::Cos(angle_rad);
        float y = radius * Ogre::Math::Sin(angle_rad);
        polar_grid_->position(x, y, 0);
        polar_grid_->colour(color_);
      }
    }
  }

  if (sectors_) {
    float angle_step = static_cast<float>(end_angle - start_angle) / sector_count_;
    for (int i = 0; i < sector_count_ + 1; ++i) {
      float angle_rad = Ogre::Math::PI * (start_angle + i * angle_step) / 180.f;
      float x1 = min_radius_ * Ogre::Math::Cos(angle_rad);
      float y1 = min_radius_ * Ogre::Math::Sin(angle_rad);
      float x2 = max_radius * Ogre::Math::Cos(angle_rad);
      float y2 = max_radius * Ogre::Math::Sin(angle_rad);
      polar_grid_->position(x1, y1, 0);
      polar_grid_->colour(color_);
      polar_grid_->position(x2, y2, 0);
      polar_grid_->colour(color_);
    }
  }

  polar_grid_->end();
}

void PolarGrid::setPosition(const Ogre::Vector3 &position) { scene_node_->setPosition(position); }

void PolarGrid::setOrientation(const Ogre::Quaternion &orientation) {
  scene_node_->setOrientation(orientation);
}

void PolarGrid::setScale(const Ogre::Vector3 & /* scale */) {}

void PolarGrid::setColor(float r, float g, float b, float a) {
  color_ = Ogre::ColourValue(r, g, b, a);
  rviz_rendering::MaterialManager::enableAlphaBlending(material_, color_.a);
  draw();
}

const Ogre::Vector3 &PolarGrid::getPosition() { return scene_node_->getPosition(); }

const Ogre::Quaternion &PolarGrid::getOrientation() { return scene_node_->getOrientation(); }

void PolarGrid::setUserData(const Ogre::Any & /* data */) {}

void PolarGrid::setMinRadius(float min_radius) {
  min_radius_ = min_radius;
  draw();
}

void PolarGrid::setRadiusStep(float radius_step) {
  radius_step_ = radius_step;
  draw();
}

void PolarGrid::setCirclesCount(int circles_count) {
  circles_count_ = circles_count;
  draw();
}

void PolarGrid::setSectors(bool sectors) {
  sectors_ = sectors;
  draw();
}

void PolarGrid::setMinAngle(int min_angle) {
  min_angle_ = min_angle;
  draw();
}

void PolarGrid::setMaxAngle(int max_angle) {
  max_angle_ = max_angle;
  draw();
}

void PolarGrid::setSectorCount(int sector_count) {
  sector_count_ = sector_count;
  draw();
}

void PolarGrid::setInvert(bool invert) {
  invert_ = invert;
  draw();
}

std::shared_ptr<Ogre::SceneNode> PolarGrid::getSceneNode() { return scene_node_; }

}  // namespace polar_grid_rviz_plugins
