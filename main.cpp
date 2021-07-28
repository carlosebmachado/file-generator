#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"
#include "watch.h"

// MESSAGES
const std::string STR_NO_COMMANDS_ENTERED    = "No commands entered.";
const std::string STR_PARAMETERS_ARE_MISSING = "Parameters are missing.";
const std::string STR_NOT_A_COMMAND          = "not a command.";
const std::string STR_UNNABLE_TO_WRITE_FILE  = "Unnable to write file.";
const std::string STR_FILE_GENERATED         = "File generated.";
const std::string STR_THIS_FUNCTION          = "This function ";
const std::string STR_WRONG_TYPE             = "This is not a type of unit.";

// LEVEL ONE
const std::string STR_CLS        = "cls";
const std::string STR_EXIT       = "exit";
const std::string STR_HELP       = "help";
const std::string STR_WRITE_FILE = "wf";

// LEVEL TWO: WRITE FILE
const std::string STR_BYTE     = "b";
const std::string STR_KILOBYTE = "kb";
const std::string STR_MEGABYTE = "mb";


const int SIZE_BYTE = 1;
const int SIZE_KILOBYTE = SIZE_BYTE * 1024;
const int SIZE_MEGABYTE = SIZE_KILOBYTE * 1024;

enum { TYPE_BYTE, TYPE_KILOBYTE, TYPE_MEGABYTE };
enum { SUCCESS, OPEN_FILE_FAILURE, WRONG_TYPE };

bool running = true;


// FILE WRITER FUNCTIONS

int getTypeSize(int type, int size) {
    size_t tsize = 0;
    switch (type) {
        case TYPE_BYTE:     tsize = SIZE_BYTE;     break;
        case TYPE_KILOBYTE: tsize = SIZE_KILOBYTE; break;
        case TYPE_MEGABYTE: tsize = SIZE_MEGABYTE; break;
        default: return -1;                        break;
    }
    return tsize;
}

int write(int type, int size, std::string file_name) {
    const unsigned char STR_BYTE = 0b01111111;
    std::ofstream file(file_name, std::ios_base::binary);
    // changed to primitive type to improve performance
    unsigned char* data;
    size_t wordSize = getTypeSize(type, size);
    size_t dataSize = 0;

    if (wordSize == -1) {
        return WRONG_TYPE;
    }

    dataSize = (size * wordSize);
    data = new unsigned char[dataSize + 1];

    for (size_t i = 0; i < dataSize; i++) {
        data[i] = STR_BYTE;
    }
    // null last char
    data[dataSize] = '\0';

    if (file.is_open()) {
        file << data;
        file.close();
        return SUCCESS;
    }

    return OPEN_FILE_FAILURE;
}

bool isGB(int type, int size) {
    int typeSize = getTypeSize(type, size);
    return typeSize != -1 ? (size * typeSize >= SIZE_MEGABYTE * 1024) : false;
}


// INTERFACE RESOURCES

void nline(int count = 1) {
    for (size_t i = 0; i < count; i++) {
        std::cout << std::endl;
    }
}

void headerMessage() {
    std::cout << "File generator v1.0";
    nline(2);
}

void waitCommandMessage() {
    std::cout << "cmd>>";
}

void success(std::string e, int line = 1) {
    std::cout << "SUCCESS: " << e;
    nline(line);
}

void exception(std::string e, int line = 1) {
    std::cout << "ERROR: " << e;
    nline(line);
}

void exception(std::string cmd, std::string e, int line = 1) {
    std::cout << cmd << " " << e;
    nline(line);
}

void print(std::string str) {
    std::cout << str;
}

void printl(std::string str) {
    std::cout << str;
    nline(1);
}

bool question_yn(std::string question) {
    std::string a;

    print(question + " [y/n]? ");
    getline(std::cin, a);

    return str_tolower(a)._Equal("y");
}


// COMMAND IMPLEMENTATIONS

bool cmd_null(char cmd) {
    return cmd == (char)0 ? true : false;
}

void cmd_help() {
    printl("These shell commands are defined internally. Type 'help' to see this list.");
    printl("Type '" + STR_HELP + " name' to find out more about the function 'name'.");
    nline(1);
    printl(STR_WRITE_FILE + " [" + STR_BYTE + " " + STR_KILOBYTE + " " + STR_MEGABYTE + "] [size] [file name]");
    printl(STR_CLS);
    printl(STR_EXIT);
    nline(1);
}

void cmd_help_cls() {
    printl(STR_THIS_FUNCTION + "clears the console.");
    nline(1);
}

void cmd_help_exit() {
    printl(STR_THIS_FUNCTION + "exits the program.");
    nline(1);
}

void cmd_help_wf() {
    printl(STR_THIS_FUNCTION + "write a file. First parameter is size type, second parameter is size and last is file name.");
    nline(1);
}

void cmd_cls() {
    system(STR_CLS.c_str());
}

void cmd_exit() {
    running = false;
}

void cmd_write_file(int type, std::string strSize, std::string path) {
    bool make = true;
    int size;

    try {
        size = stoi(strSize);
    } catch (...) {
        exception("Invalid argument '" + strSize + "'.", 2);
        return;
    }

    if (isGB(type, size) && !question_yn("Make files over 1GB may take time. Are you sure you want to continue")) {
        make = false;
    }

    if (make) {
        Stopwatch sw = Stopwatch();
        sw.start();
        auto result = write(type, size, path);
        if (result == SUCCESS) {
            success(STR_FILE_GENERATED);
        } else if (result == OPEN_FILE_FAILURE) {
            exception(STR_UNNABLE_TO_WRITE_FILE);
        } else if (result == WRONG_TYPE) {
            exception(STR_WRONG_TYPE);
        }
        sw.stop();
        std::cout << "Time: " << sw.getElapsed() << "ms";
        nline(2);
    } else {
        printl("Aborted.");
        nline(1);
    }
}

void parse(std::string cmd) {
    size_t cmdSize = 0;
    std::string* scmd;

    cmd = trim(remove_extra_whitespaces(cmd));
    cmdSize = std::count(cmd.begin(), cmd.end(), ' ') + 1;
    scmd = split(cmd);

    if (cmdSize > 0) {
        scmd[0] = str_tolower(scmd[0]);
    }
    if (cmd_null(scmd[0][0])) {
        exception(STR_NO_COMMANDS_ENTERED, 2);
    } else if (scmd[0]._Equal(STR_HELP)) {
        if (cmdSize > 1) {
            scmd[1] = str_tolower(scmd[1]);
        }
        if (cmdSize == 1) {
            cmd_help();
        } else if (scmd[1]._Equal(STR_CLS)) {
            cmd_help_cls();
        } else if (scmd[1]._Equal(STR_EXIT)) {
            cmd_help_exit();
        } else if (scmd[1]._Equal(STR_WRITE_FILE)) {
            cmd_help_wf();
        } else {
            exception(scmd[1], STR_NOT_A_COMMAND, 2);
        }
    } else if (scmd[0]._Equal(STR_CLS)) {
        cmd_cls();
    } else if (scmd[0]._Equal(STR_EXIT)) {
        cmd_exit();
    } else if (scmd[0]._Equal(STR_WRITE_FILE)) {
        if (cmdSize > 3) {
            scmd[1] = str_tolower(scmd[1]);
        }
        if (cmdSize < 3) {
            exception(STR_PARAMETERS_ARE_MISSING, 2);
        } else if (scmd[1]._Equal(STR_BYTE)) {
            cmd_write_file(TYPE_BYTE, scmd[2], scmd[3]);
        } else if (scmd[1]._Equal(STR_KILOBYTE)) {
            cmd_write_file(TYPE_KILOBYTE, scmd[2], scmd[3]);
        } else if (scmd[1]._Equal(STR_MEGABYTE)) {
            cmd_write_file(TYPE_MEGABYTE, scmd[2], scmd[3]);
        } else {
            cmd_write_file(TYPE_BYTE, scmd[1], scmd[2]);
        }
    } else {
        exception(scmd[0], STR_NOT_A_COMMAND, 2);
    }
}

int main() {
    std::string cmd = "";

    headerMessage();
    do {
        waitCommandMessage();
        getline(std::cin, cmd);
        parse(cmd);
    } while (running);

    return EXIT_SUCCESS;
}
