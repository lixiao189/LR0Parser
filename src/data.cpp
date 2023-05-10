#include "data.h"

std::string LR0_STR = R"(S->E
E->aA
E->bB
A->cA
A->d
B->cB
B->d
)"; // 最后一行表达式一定要以 \n 结尾，要不然无法识别