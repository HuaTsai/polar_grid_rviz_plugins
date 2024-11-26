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
