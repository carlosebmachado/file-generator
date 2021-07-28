#pragma once

// Lib: https://github.com/carlosebmachado/util

#include <iostream>
#include <algorithm>
#include <cctype>


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

std::string str_tolower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
    return str;
}

std::string remove_extra_whitespaces(std::string input) {
    std::string output = "";
    auto inputSize = input.size();

    for (size_t i = 0; i < inputSize; ++i) {
        auto c = input[i];
        output += c;
        if (c == ' ') {
            while (i < inputSize && c == ' ') {
                ++i;
                c = input[i];
            }
            --i;
        }
    }
    return output;
}

// Remove spaces in the begin of a string.
std::string trimLeft(std::string string)
{
    size_t begin = 0;
    for (size_t i = 0; i < string.size(); i++)
    {
        if (string[i] != ' ')
        {
            begin = i;
            break;
        }
    }
    return string.substr(begin, string.size());
}

// Remove spaces in the end of a string.
std::string trimRight(std::string string)
{
    size_t end = 0;
    for (size_t i = string.size(); i > 0; i--)
    {
        if (string[i - 1] != ' ')
        {
            end = i;
            break;
        }
    }
    return string.substr(0, end);
}

// Remove spaces in the begin and end of a string.
std::string trim(std::string string)
{
    return trimLeft(trimRight(string));
}
