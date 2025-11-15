#ifndef ASSIGNMENT_03_INTERPRETER_H
#define ASSIGNMENT_03_INTERPRETER_H

#include <string>
#include "AVL.h"
#include "Parser.h"

class Interpreter {
private:
    AVL symbolTable;
    Parser parser;

    [[nodiscard]] bool IsAssignment(const std::string &input) const;
    std::string ExtractVariableName(const std::string& input) const;
    std::string ExtractExpression(const std::string &input) const;

public:
    Interpreter();

    double Process(const std::string& input);


};


#endif //ASSIGNMENT_03_INTERPRETER_H