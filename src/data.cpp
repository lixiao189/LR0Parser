#include "data.h"

// 输入数据必须是增广文法
std::string LR0_STR = R"(S->E
E->aA
E->bB
A->cA
A->d
B->cB
B->d)";