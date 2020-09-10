#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>
#include <assert.h>

class FileGenerator {
private:
    const char* STR_BYTE = "0";
    const unsigned short MULTIPLIER = 1024;
    const unsigned short BYTE = 1;
    const unsigned short KILOBYTE = MULTIPLIER;
    const unsigned short MEGABYTE = KILOBYTE * MULTIPLIER;
    const unsigned short GIGABYTE = MEGABYTE * MULTIPLIER;
    const unsigned short TERABYTE = GIGABYTE * MULTIPLIER;

public:
    enum { B, KB, MB, GB, TB };
    enum { SUCCESS, OPEN_FILE_FAILURE, WRONG_TYPE };

    int write(int type, int size, std::string file_name) {
        std::ofstream file(file_name, std::ios_base::binary);
        std::string word = "";
        long long wordSize = 0;

        switch (type) {
        case B:  wordSize = BYTE;     break;
        case KB: wordSize = KILOBYTE; break;
        case MB: wordSize = MEGABYTE; break;
        case GB: wordSize = GIGABYTE; break;
        case TB: wordSize = TERABYTE; break;
        default: return WRONG_TYPE;   break;
        }

        for (long long i = 0; i < wordSize; i++) {
            word += STR_BYTE;
        }

        if (file.is_open()) {
            for (long long i = 0; i < size; i++) {
                file << word;
            }
            file.close();
            return SUCCESS;
        }
        return OPEN_FILE_FAILURE;
    }
};
