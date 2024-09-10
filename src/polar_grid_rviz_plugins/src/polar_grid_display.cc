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
#include <polar_grid_rviz_plugins/polar_grid.hpp>
#include <polar_grid_rviz_plugins/polar_grid_display.hpp>
#include <rviz_common/logging.hpp>
#include <rviz_rendering/material_manager.hpp>

namespace polar_grid_rviz_plugins {

void PolarGridDisplay::onInitialize() {
  Display::onInitialize();

  polar_grid_shape_ = std::make_unique<PolarGrid>(scene_manager_);

  color_property_ = std::make_unique<rviz_common::properties::ColorProperty>(
      "Color", Qt::gray, "The color of the circles.", this,
      SLOT(updateColor()));
  alpha_property_ = std::make_unique<rviz_common::properties::FloatProperty>(
      "Alpha", 0.5f, "The amount of transparency to apply to the circles.",
      this, SLOT(updateColor()));
  alpha_property_->setMin(0.f);
  alpha_property_->setMax(1.f);

  updateColor();

  auto grid = std::make_unique<PolarGrid>(scene_manager_);
}

void PolarGridDisplay::updateColor() {
  // Ogre::ColourValue color = color_property_->getOgreColor();
  // color.a = alpha_property_->getFloat();
  // polar_grid_shape_->setColor(color);
}

}  // namespace polar_grid_rviz_plugins

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(polar_grid_rviz_plugins::PolarGridDisplay,
                       rviz_common::Display)
