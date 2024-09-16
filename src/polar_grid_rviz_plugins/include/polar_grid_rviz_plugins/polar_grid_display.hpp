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
#pragma once

#include <polar_grid_rviz_plugins/polar_grid.hpp>
#include <rviz_common/display.hpp>
#include <rviz_common/properties/color_property.hpp>
#include <rviz_common/properties/enum_property.hpp>
#include <rviz_common/properties/float_property.hpp>
#include <rviz_common/properties/int_property.hpp>
#include <rviz_common/properties/tf_frame_property.hpp>
#include <rviz_common/properties/vector_property.hpp>

namespace polar_grid_rviz_plugins
{

class PolarGridDisplay : public rviz_common::Display {
  Q_OBJECT

public:
  enum class Plane
  {
    kXY,
    kXZ,
    kYZ,
  };
  PolarGridDisplay();
  void onInitialize() override;
  void update(float dt, float ros_dt) override;

private Q_SLOTS:
  void updateColor();
  void updateMinRadius();
  void updateRadiusStep();
  void updateCirclesCount();
  void updatePlane();
  void updateSectors();
  void updateMinAngle();
  void updateMaxAngle();
  void updateSectorCount();
  void updateInvert();
  void updateOffset();

protected:
  std::unique_ptr<PolarGrid> polar_grid_;
  std::unique_ptr<rviz_common::properties::TfFrameProperty> frame_property_;
  std::unique_ptr<rviz_common::properties::ColorProperty> color_property_;
  std::unique_ptr<rviz_common::properties::FloatProperty> alpha_property_;
  std::unique_ptr<rviz_common::properties::FloatProperty> min_radius_property_;
  std::unique_ptr<rviz_common::properties::FloatProperty> radius_step_property_;
  std::unique_ptr<rviz_common::properties::IntProperty> circles_count_property_;
  std::unique_ptr<rviz_common::properties::EnumProperty> plane_property_;
  std::unique_ptr<rviz_common::properties::BoolProperty> sectors_property_;
  std::unique_ptr<rviz_common::properties::IntProperty> min_angle_property_;
  std::unique_ptr<rviz_common::properties::IntProperty> max_angle_property_;
  std::unique_ptr<rviz_common::properties::IntProperty> sector_count_property_;
  std::unique_ptr<rviz_common::properties::BoolProperty> invert_property_;
  std::unique_ptr<rviz_common::properties::VectorProperty> offset_property_;
};

}  // namespace polar_grid_rviz_plugins
