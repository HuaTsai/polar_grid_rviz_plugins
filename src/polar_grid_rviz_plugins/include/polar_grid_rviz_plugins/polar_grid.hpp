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
#pragma once

#include <rviz_rendering/objects/object.hpp>

namespace polar_grid_rviz_plugins {

class PolarGrid : public rviz_rendering::Object {
 public:
  explicit PolarGrid(Ogre::SceneManager *scene_manager);

  void setPosition(const Ogre::Vector3 & position) override;
  void setOrientation(const Ogre::Quaternion & orientation) override;
  void setScale(const Ogre::Vector3 & scale) override;
  void setColor(float r, float g, float b, float a) override;
  const Ogre::Vector3 & getPosition() override;
  const Ogre::Quaternion & getOrientation() override;
  void setUserData(const Ogre::Any & data) override;

 private:
  std::shared_ptr<Ogre::SceneNode> scene_node_;
  std::vector<std::shared_ptr<Ogre::ManualObject>> polars_;
};

}  // namespace polar_grid_rviz_plugins
