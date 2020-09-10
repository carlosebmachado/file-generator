#pragma once

#include <iostream>

class StringHandle {
public:
    std::string* split(std::string cmd) {
        int curIdx = 0;
        int spaces = countSpaces(cmd);
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

    int clamp(int num, int min, int max) {
        if (num > max)return max;
        if (num < min)return min;
        return num;
    }

    int countSpaces(std::string cmd)
    {
        int amt = 0;
        for (size_t i = 0; i < cmd.size(); i++) {
            if (cmd[i] == ' ') {
                amt++;
            }
        }
        return amt;
    }
};
