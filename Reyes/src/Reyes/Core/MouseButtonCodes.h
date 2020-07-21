#pragma once

#define REY_MB_1         1
#define REY_MB_2         2
#define REY_MB_3         3
#define REY_MB_4         4
#define REY_MB_5         5
#define REY_MB_6         6
#define REY_MB_7         7
#define REY_MB_8         8
#define REY_MB_LEFT      REY_MB_1
#define REY_MB_RIGHT     REY_MB_2
#define REY_MB_MIDDLE    REY_MB_3

#define REY_MB_TO_GLFW(button) button - 1
#define REY_MB_FROM_GLFW(button) button + 1