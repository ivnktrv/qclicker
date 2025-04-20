#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

std::vector<std::tuple<int, int, int>> setPos(bool onlyClick = false);
int simulation(bool onlyClick = false, int delay = 10, bool cyclic = false);
int autoClicker(int delay);
int getCursorPosition();

#endif