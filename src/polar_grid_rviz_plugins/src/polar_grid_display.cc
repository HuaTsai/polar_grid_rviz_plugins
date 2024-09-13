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
#include <polar_grid_rviz_plugins/polar_grid_display.hpp>
#include <rviz_common/display_context.hpp>
#include <rviz_common/logging.hpp>
#include <rviz_rendering/material_manager.hpp>

namespace polar_grid_rviz_plugins {

PolarGridDisplay::PolarGridDisplay() {
  frame_property_ = std::make_unique<rviz_common::properties::TfFrameProperty>(
      "Reference Frame", rviz_common::properties::TfFrameProperty::FIXED_FRAME_STRING,
      "The TF frame this polar grid will use for its origin.", this, nullptr, true);

  color_property_ = std::make_unique<rviz_common::properties::ColorProperty>(
      "Color", Qt::gray, "The color of the circles.", this, SLOT(updateColor()));
  alpha_property_ = std::make_unique<rviz_common::properties::FloatProperty>(
      "Alpha", 0.5f, "The amount of transparency to apply to the circles.", this,
      SLOT(updateColor()));
  alpha_property_->setMin(0.f);
  alpha_property_->setMax(1.f);

  min_radius_property_ = std::make_unique<rviz_common::properties::FloatProperty>(
      "Minimum Radius", 0.0f, "The minimum radius of the polar grid.", this,
      SLOT(updateMinRadius()));
  min_radius_property_->setMin(0.f);

  radius_step_property_ = std::make_unique<rviz_common::properties::FloatProperty>(
      "Radius Step", 1.0f, "The step size for radius increments.", this, SLOT(updateRadiusStep()));
  radius_step_property_->setMin(0.f);

  circles_count_property_ = std::make_unique<rviz_common::properties::IntProperty>(
      "Circles Count", 5, "The number of circles to draw.", this, SLOT(updateCirclesCount()));
  circles_count_property_->setMin(0);

  plane_property_ = std::make_unique<rviz_common::properties::EnumProperty>(
      "Plane", "XY", "The plane to draw the polar grid along.", this, SLOT(updatePlane()));
  plane_property_->addOption("XY", static_cast<int>(Plane::kXY));
  plane_property_->addOption("XZ", static_cast<int>(Plane::kXZ));
  plane_property_->addOption("YZ", static_cast<int>(Plane::kYZ));

  // TODO(HuaTsai): boarder (ang1, ang2), invert, origin offset, show texts and their color/size
}

void PolarGridDisplay::onInitialize() {
  Display::onInitialize();

  frame_property_->setFrameManager(context_->getFrameManager());

  polar_grid_ = std::make_unique<PolarGrid>(scene_manager_, scene_node_);

  updateColor();
  updateMinRadius();
  updateRadiusStep();
  updateCirclesCount();
  updatePlane();
}

void PolarGridDisplay::update(float /* dt */, float /* ros_dt */) {
  std::string frame = frame_property_->getFrame().toStdString();

#if (defined(ROS_DISTRO_GALACTIC))
  Ogre::Vector3 position;
  Ogre::Quaternion orientation;
  if (context_->getFrameManager()->getTransform(frame, position, orientation)) {
    scene_node_->setPosition(position);
    scene_node_->setOrientation(orientation);
#else
  if (updateFrame(frame)) {
#endif
    setTransformOk();
    polar_grid_->getSceneNode()->setVisible(true);
  } else {
    setMissingTransformToFixedFrame(frame);
    polar_grid_->getSceneNode()->setVisible(false);
  }
}

void PolarGridDisplay::updateColor() {
  Ogre::ColourValue color = color_property_->getOgreColor();
  color.a = alpha_property_->getFloat();
  polar_grid_->setColor(color.r, color.g, color.b, color.a);
  // context_->queueRender();  // FIXME: check if this is necessary
}

void PolarGridDisplay::updateMinRadius() {
  polar_grid_->setMinRadius(min_radius_property_->getFloat());
}

void PolarGridDisplay::updateRadiusStep() {
  polar_grid_->setRadiusStep(radius_step_property_->getFloat());
}

void PolarGridDisplay::updateCirclesCount() {
  polar_grid_->setCirclesCount(circles_count_property_->getInt());
}

void PolarGridDisplay::updatePlane() {
  Ogre::Quaternion q;
  Plane plane = static_cast<Plane>(plane_property_->getOptionInt());
  if (plane == Plane::kXY) {
    q = Ogre::Quaternion(Ogre::Vector3::UNIT_X, Ogre::Vector3::UNIT_Y, Ogre::Vector3::UNIT_Z);
  } else if (plane == Plane::kXZ) {
    q = Ogre::Quaternion(Ogre::Vector3::UNIT_X, Ogre::Vector3::UNIT_Z, -Ogre::Vector3::UNIT_Y);
  } else if (plane == Plane::kYZ) {
    q = Ogre::Quaternion(Ogre::Vector3::UNIT_Y, Ogre::Vector3::UNIT_Z, Ogre::Vector3::UNIT_X);
  } else {
    RVIZ_COMMON_LOG_ERROR_STREAM("Invalid plane index " << plane_property_->getOptionInt());
  }
  polar_grid_->getSceneNode()->setOrientation(q);
}

}  // namespace polar_grid_rviz_plugins

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(polar_grid_rviz_plugins::PolarGridDisplay, rviz_common::Display)
