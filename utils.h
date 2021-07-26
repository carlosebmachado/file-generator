#pragma once

#include <iostream>

int clamp(int num, int min, int max) {
    if (num > max)return max;
    if (num < min)return min;
    return num;
}

std::string* split(std::string cmd) {
    int curIdx = 0;
    int spaces = std::count(cmd.begin(), cmd.end(), ' ');
    int size = spaces + 1;
    std::string* splitted = new std::string[size];
    for (size_t i = 0; i < cmd.size(); i++) {
        if (cmd[i] == ' ') {
            curIdx++;
            curIdx = clamp(curIdx, 0, size - 1);
            continue;
        }
        splitted[curIdx] += cmd[i];
    }
    return splitted;
}
