# polar_grid_rviz_plugins

[![humble | iron | jazzy | rolling](https://github.com/HuaTsai/polar_grid_rviz_plugins/actions/workflows/ros2.yml/badge.svg)](https://github.com/HuaTsai/polar_grid_rviz_plugins/actions/workflows/ros2.yml)

Show polar grid in rviz

![Demo](docs/demo.gif)

| Settings        | Type                  | Default values       |
| --------------- | --------------------- | -------------------- |
| Reference Frame | string                | \<Fixed Frame\>      |
| RGB Color       | (int, int, int)       | Grey (160, 160, 164) |
| Alpha           | fp                    | 0.5                  |
| Minimum Radius  | fp                    | 0.0                  |
| Radius Step     | fp                    | 1.0                  |
| Circles Count   | int                   | 5                    |
| Plane           | enum (XY \| XZ \| YZ) | XY                   |
| Sectors         | bool                  | False                |
| Minimum Angle   | fp (>= -180.0)        | -180.0               |
| Maximum Angle   | fp (<= 180.0)         | 180.0                |
| Sector Count    | int                   | 8                    |
| Invert          | bool                  | False                |
| Offset          | (fp, fp, fp)          | (0.0, 0.0, 0.0)      |

\*fp: floating point

## Usage

1. Via git

   ```bash
   mkdir src
   cd src
   git clone git@github.com:HuaTsai/polar_grid_rviz_plugins.git
   cd ..
   colcon build
   source install/setup.bash
   rviz2
   ```

2. Via vcs

   Add following content to `ros2.repos` file in your workspace

   ```text
   repositories:
     polar_grid_rviz_plugins:
       type: git
       url: git@github.com:HuaTsai/polar_grid_rviz_plugins.git
       version: v1.0.0
   ```

   ```bash
   mkdir src
   vcs import src < ros2.repos
   colcon build
   source install/setup.bash
   rviz2
   ```

3. Via prebuilt debian package

   ```bash
   sudo dpkg -i ros-rolling-polar-grid-rviz-plugins_1.0.0-0noble_amd64.deb
   ```

4. Via debian package built by system

   ```bash
   sudo apt install python3-bloom fakeroot dh-make
   git clone git@github.com:HuaTsai/polar_grid_rviz_plugins.git
   cd polar_grid_rviz_plugins
   bloom-generate rosdebian
   fakeroot debian/rules binary
   cd ..
   sudo dpkg -i <debfile>
   ```
