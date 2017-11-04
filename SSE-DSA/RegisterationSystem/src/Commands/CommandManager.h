//
// Created by 付旭炜 on 2017/9/28.
//

#ifndef REGISTERATIONSYSTEM_COMMANDMANAGER_H
#define REGISTERATIONSYSTEM_COMMANDMANAGER_H

#include "Commands.h"
#include "../StudentList.h"
#include "BaseCommand.h"
#include "Commands.h"
#include <map>

class CommandManager {
public:
    explicit CommandManager(StudentList& student_list) {
        auto insertCommand = std::make_shared<InsertCommand>(student_list);
        auto deleteCommand = std::make_shared<DeleteCommand>(student_list);
        auto selectCommand = std::make_shared<SelectCommand>(student_list);
        auto updateCommand = std::make_shared<UpdateCommand>(student_list);
        auto outputCommand = std::make_shared<OutputCommand>(student_list);
        code_to_operator[1] = insertCommand;
        code_to_operator[2] = deleteCommand;
        code_to_operator[3] = selectCommand;
        code_to_operator[4] = updateCommand;
        code_to_operator[5] = outputCommand;
    }

    void excute(int code) {
        if (code == 0) {
            undo();
            return;
        }
        auto command_ptr = code_to_operator[code];
        if (command_ptr == nullptr) {
            std::cout << "Input Error\n";
            return;
        }
        command_ptr->excute();
        precommand = command_ptr;
    }

    void undo() {
        if (precommand == nullptr) {
            std::cout << "Have been undo or didn't do anything\n";
        }
        precommand->undo();
        precommand = nullptr;
    }

private:
    std::map<int, std::shared_ptr<BaseCommand>> code_to_operator;
    std::shared_ptr<BaseCommand> precommand = nullptr;
};


#endif //REGISTERATIONSYSTEM_COMMANDMANAGER_H
