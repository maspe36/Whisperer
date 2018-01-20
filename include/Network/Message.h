//
// Created by Sam on 1/15/2018.
//

#ifndef WHISPERERENGINE_MESSAGE_H
#define WHISPERERENGINE_MESSAGE_H

#include <string>
#include "../Game/Utilities/Exportable.h"


class Message: public Exportable
{
public:
    std::string type;
    std::string data;

    void buildJSON();

    Message(std::string type, std::string data);
    Message(std::string json);
    ~Message();
};


#endif //WHISPERERENGINE_MESSAGE_H
