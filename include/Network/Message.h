//
// Created by Sam on 1/15/2018.
//

#ifndef WHISPERERENGINE_MESSAGE_H
#define WHISPERERENGINE_MESSAGE_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Message
{
public:
    static std::string SUCCESS;
    static std::string FAILURE;
    static std::string LOGIN;
    static std::string QUEUE;
    static std::string REGISTER_PLAYER;
    static std::string START_GAME;
    static std::string PLAY_CARD;

    static std::string SEND_CHAT;

    static std::string TYPE_KEY;
    static std::string DATA_KEY;

    json rawJSON;

    std::string getJSON();
    void loadJSON(std::string json);
    void loadJSON(const json& newJSON);
    void addDataMember(std::string key, json value);

    std::string getType();
    std::string getMember(std::string key);
    std::string getDataMember(std::string key);

    static const std::string success();
    static const std::string fail(std::string cause);
    static const std::string login();
    static const std::string registerPlayer();

    explicit Message(std::string type);
    Message();
    virtual ~Message();
};


#endif //WHISPERERENGINE_MESSAGE_H
