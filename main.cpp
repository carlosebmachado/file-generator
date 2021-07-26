#include <iostream>
#include "fileh.h"
#include "utils.h"
#include "watch.h"

class Application {
private:
    // MESSAGES
    const std::string NO_COMMANDS_ENTERED = "No commands entered.";
    const std::string PARAMETERS_ARE_MISSING = "Parameters are missing.";
    const std::string NOT_A_COMMAND = "not a command.";
    const std::string UNNABLE_TO_WRITE_FILE = "Unnable to write file.";
    const std::string FILE_GENERATED = "File generated.";
    const std::string THIS_FUNCTION = "This function ";
    const std::string WRONG_TYPE = "This is not a type of unit.";

    // LEVEL ONE
    const std::string CLS = "cls";
    const std::string EXIT = "exit";
    const std::string HELP = "help";
    const std::string WRITE_FILE = "wf";

    // LEVEL TWO: WRITE FILE
    const std::string B = "b";
    const std::string KB = "kb";
    const std::string MB = "mb";
    const std::string GB = "gb";
    const std::string TB = "tb";

    bool running = true;
    size_t cmdSize = 0;
    std::string cmd = "";
    std::string* scmd;

public:
    int run() {
        headerMessage();
        do {
            waitCommandMessage();
            getline(std::cin, cmd);
            cmdSize = std::count(cmd.begin(), cmd.end(), ' ') + 1;
            scmd = split(cmd);
            parse();
        } while (running);
        return EXIT_SUCCESS;
    }

private:
    void parse() {
        if (cmd_null()) {
            exception(NO_COMMANDS_ENTERED, 2);
        }
        else if (scmd[0]._Equal(HELP)) {
            if (cmdSize == 1) {
                cmd_help();
            }
            else if (scmd[1]._Equal(CLS)) {
                cmd_help_cls();
            }
            else if (scmd[1]._Equal(EXIT)) {
                cmd_help_exit();
            }
            else if (scmd[1]._Equal(WRITE_FILE)) {
                cmd_help_wf();
            }
            else {
                exception(scmd[1], NOT_A_COMMAND, 2);
            }
        }
        else if (scmd[0]._Equal(CLS)) {
            cmd_cls();
        }
        else if (scmd[0]._Equal(EXIT)) {
            cmd_exit();
        }
        else if (scmd[0]._Equal(WRITE_FILE)) {
            if (cmdSize < 4) {
                exception(PARAMETERS_ARE_MISSING);
            }
            else if (scmd[1]._Equal(B)) {
                cmd_wf_bt();
            }
            else if (scmd[1]._Equal(KB)) {
                cmd_wf_kb();
            }
            else if (scmd[1]._Equal(MB)) {
                cmd_wf_mb();
            }
            else if (scmd[1]._Equal(GB)) {
                cmd_wf_gb();
            }
            else if (scmd[1]._Equal(TB)) {
                cmd_wf_tb();
            }
            else {
                exception(scmd[1], NOT_A_COMMAND, 2);
            }
        }
        else {
            exception(scmd[0], NOT_A_COMMAND, 2);
        }
    }

    bool cmd_null() {
        return scmd[0][0] == (char)0 ? true : false;
    }

    void cmd_help() {
        printl("These shell commands are defined internally. Type 'help' to see this list.");
        printl("Type '" + HELP + " name' to find out more about the function 'name'.");
        nline(1);
        printl(WRITE_FILE + " [" + B + " " + KB + " " + MB + " " + GB + " " + TB + "] [size] [file name]");
        printl(CLS);
        printl(EXIT);
        nline(1);
    }

    void cmd_help_cls() {
        printl(THIS_FUNCTION + "clears the console.");
        nline(1);
    }

    void cmd_help_exit() {
        printl(THIS_FUNCTION + "exits the program.");
        nline(1);
    }

    void cmd_help_wf() {
        printl(THIS_FUNCTION + "write a file. First parameter is size type, second parameter is size and last is file name.");
        nline(1);
    }

    void cmd_cls() {
        system(CLS.c_str());
    }

    void cmd_exit() {
        running = false;
    }

    void cmd_wf_bt() {
        wf_generic(FileGenerator().B);
    }

    void cmd_wf_kb() {
        wf_generic(FileGenerator().KB);
    }

    void cmd_wf_mb() {
        wf_generic(FileGenerator().MB);
    }

    void cmd_wf_gb() {
        big_files(FileGenerator().GB);
    }

    void cmd_wf_tb() {
        big_files(FileGenerator().TB);
    }

    void big_files(int type) {
        if (question_yn("Make files over 1GB may take time. Are you sure you want to continue")) {
            wf_generic(type);
        }
        else {
            printl("Aborted.");
            nline(1);
        }
    }

    void wf_generic(int type) {
        Stopwatch sw = Stopwatch();
        sw.start();
        sf_message(FileGenerator().write(type, std::stoi(scmd[2]), scmd[3]));
        sw.stop();
        std::cout << "Time: " << sw.getElapsed() << "ms";
        nline(2);
    }

    void sf_message(int result) {
        if (result == FileGenerator().SUCCESS) {
            success(FILE_GENERATED);
        }
        else if (result == FileGenerator().OPEN_FILE_FAILURE) {
            exception(UNNABLE_TO_WRITE_FILE);
        }
        else if (result == FileGenerator().WRONG_TYPE) {
            exception(WRONG_TYPE);
        }
    }

    bool question_yn(std::string question) {
        std::string a;
        do {
            print(question + " [y/n]? ");
            getline(std::cin, a);
            if (a._Equal("y") || a._Equal("Y")) {
                return true;
            }
            else if (a._Equal("n") || a._Equal("N")) {
                return false;
            }
            printl("Please, type Y or N.");
        } while (true);
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

    void nline(int amt = 1) {
        for (size_t i = 0; i < amt; i++) {
            std::cout << std::endl;
        }
    }
};

int main() {
    Application().run();
}
