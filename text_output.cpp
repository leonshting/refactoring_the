//
// Created by leonsht on 3/10/16.
//

#include "text_output.h"

text_output::text_output(VectorXd &answer, settings &S, init_data &it):Answer(answer), Settings(S), initData(it)
{
    cAnswer = cAnswer_fromD(Answer);
}

VectorXcd text_output::cAnswer_fromD(VectorXd &answer) {
    int csize = answer.rows()/2;
    VectorXd ret(csize);
    for(int i = 0 ; i < csize; i++)
       ret(i) = cd(answer(i), answer(csize+i));
    return ret;
}
