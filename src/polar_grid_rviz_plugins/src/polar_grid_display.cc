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
#include <polar_grid_rviz_plugins/polar_grid_display.hpp>
#include <rviz_common/display_context.hpp>
#include <rviz_common/logging.hpp>
#include <rviz_rendering/material_manager.hpp>

namespace polar_grid_rviz_plugins {

PolarGridDisplay::PolarGridDisplay() {
  frame_property_ = std::make_unique<rviz_common::properties::TfFrameProperty>(
      "Reference Frame",
      rviz_common::properties::TfFrameProperty::FIXED_FRAME_STRING,
      "The TF frame this polar grid will use for its origin.", this, nullptr,
      true);

  color_property_ = std::make_unique<rviz_common::properties::ColorProperty>(
      "Color", Qt::gray, "The color of the circles.", this,
      SLOT(updateColor()));
  alpha_property_ = std::make_unique<rviz_common::properties::FloatProperty>(
      "Alpha", 0.5f, "The amount of transparency to apply to the circles.",
      this, SLOT(updateColor()));
  alpha_property_->setMin(0.f);
  alpha_property_->setMax(1.f);
}

void PolarGridDisplay::onInitialize() {
  Display::onInitialize();

  frame_property_->setFrameManager(context_->getFrameManager());

  polar_grid_ = std::make_unique<PolarGrid>(scene_manager_, scene_node_);

  updateColor();

  polar_grid_->draw();
}

void PolarGridDisplay::update(float dt, float ros_dt) {
  (void)dt;
  (void)ros_dt;
  QString qframe = frame_property_->getFrame();
  std::string frame = qframe.toStdString();

  if (updateFrame(frame)) {
    setTransformOk();
    polar_grid_->getSceneNode()->setVisible(true);
  } else {
    setMissingTransformToFixedFrame(qframe.toStdString());
    polar_grid_->getSceneNode()->setVisible(false);
  }
}

void PolarGridDisplay::updateColor() {
  Ogre::ColourValue color = color_property_->getOgreColor();
  color.a = alpha_property_->getFloat();
  polar_grid_->setColor(color.r, color.g, color.b, color.a);
  // context_->queueRender();  // FIXME: check if this is necessary
}

}  // namespace polar_grid_rviz_plugins

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(polar_grid_rviz_plugins::PolarGridDisplay,
                       rviz_common::Display)
