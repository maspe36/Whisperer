//
// Created by Sam on 1/3/2018.
//

#ifndef WHISPERERENGINE_EXPORTABLE_H
#define WHISPERERENGINE_EXPORTABLE_H


#include <string>


class Exportable
{
public:
    const std::string tag;

    Exportable();
    virtual ~Exportable();
};


#endif //WHISPERERENGINE_EXPORTABLE_H