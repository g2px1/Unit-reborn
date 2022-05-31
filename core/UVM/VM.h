//
// Created by Kirill Zhukov on 31.05.2022.
//

#ifndef UVM_VM_H
#define UVM_VM_H
#include <stack>
#include "vector"

typedef int64_t WORD;
constexpr WORD OP_CODE_MASK = 0b0000000000000000000000000000000000000000000000000000000011111111;
constexpr WORD OP_TYPE_MASK = 0b0000000000000000000000000000000000000000000000000000111000000000;
constexpr WORD OP_HALT      = 0b0000000000000000000000000000000000000000000000000000000000000000;
constexpr WORD OP_CONST     = 0b0000000000000000000000000000000000000000000000000000000000000001;
constexpr WORD OP_PUSH      = 0b0000000000000000000000000000000000000000000000000000000000000010;
constexpr WORD OP_POP       = 0b0000000000000000000000000000000000000000000000000000000000000011;
constexpr WORD OP_INC       = 0b0000000000000000000000000000000000000000000000000000000000000100;
constexpr WORD OP_DEC       = 0b0000000000000000000000000000000000000000000000000000000000000101;
constexpr WORD OP_ADD       = 0b0000000000000000000000000000000000000000000000000000000000000110;
constexpr WORD OP_SUB       = 0b0000000000000000000000000000000000000000000000000000000000000111;
constexpr WORD OP_MUL       = 0b0000000000000000000000000000000000000000000000000000000000001000;
constexpr WORD OP_DIV       = 0b0000000000000000000000000000000000000000000000000000000000001001;
constexpr WORD OP_AND       = 0b0000000000000000000000000000000000000000000000000000000000001010;
constexpr WORD OP_OR        = 0b0000000000000000000000000000000000000000000000000000000000001011;
constexpr WORD OP_XOR       = 0b0000000000000000000000000000000000000000000000000000000000001100;
constexpr WORD OP_NOT       = 0b0000000000000000000000000000000000000000000000000000000000001101;
constexpr WORD OP_SHL       = 0b0000000000000000000000000000000000000000000000000000000000001110;
constexpr WORD OP_SHR       = 0b0000000000000000000000000000000000000000000000000000000000001111;
constexpr WORD OP_JMP       = 0b0000000000000000000000000000000000000000000000000000000000010001;
constexpr WORD OP_CMPJE     = 0b0000000000000000000000000000000000000000000000000000000000010010;
constexpr WORD OP_CMPJNE    = 0b0000000000000000000000000000000000000000000000000000000000010011;
constexpr WORD OP_CMPJG     = 0b0000000000000000000000000000000000000000000000000000000000010100;
constexpr WORD OP_CMPJGE    = 0b0000000000000000000000000000000000000000000000000000000000010101;
constexpr WORD OP_CMPJL     = 0b0000000000000000000000000000000000000000000000000000000000010110;
constexpr WORD OP_CMPJLE    = 0b0000000000000000000000000000000000000000000000000000000000010111;
constexpr WORD OP_DUP       = 0b0000000000000000000000000000000000000000000000000000000000011000;
constexpr WORD OP_CALL      = 0b0000000000000000000000000000000000000000000000000000000000011001;
constexpr WORD OP_RET       = 0b0000000000000000000000000000000000000000000000000000000000011010;
constexpr WORD OP_SYSCALL   = 0b0000000000000000000000000000000000000000000000000000000000011011;
constexpr WORD OP_RESERVED1 = 0b0000000000000000000000000000000000000000000000000000000000011100;
constexpr WORD OP_RESERVED2 = 0b0000000000000000000000000000000000000000000000000000000000011101;
constexpr WORD OP_RESERVED3 = 0b0000000000000000000000000000000000000000000000000000000000011110;
constexpr WORD OP_RESERVED4 = 0b0000000000000000000000000000000000000000000000000000000000011111;
constexpr WORD MAX_MEMORY = 65536;

class VM {
private:
    std::stack<void*> instructions;
public:
    VM();
    virtual ~VM();
    [[noreturn]]
    void run();
    void popInstruction();
    bool pushInstruction(void* instruction);
    bool isEmptyInstructions() {
        return this->instructions.empty();
    };
    std::vector<void*> memory;
};


#endif //UVM_VM_H
