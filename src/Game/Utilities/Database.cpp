//
// Created by Sam on 2/11/2018.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "../../../include/Game/Utilities/Database.h"

std::vector<std::string> Database::getDeckCards(std::string userID, std::string deckID)
{
    std::vector<std::string> rows;

    std::string query = formatGetDeckCardsQuery(std::move(userID), std::move(deckID));
    result = PQexec(connection, query.c_str());

    for (int i = 0; i < PQntuples(result); i++)
    {
        rows.emplace_back(PQgetvalue(result, i, 0));
    }

    return rows;
}

Database::Database()
        : result(nullptr)
{
    initializeConfig();
    CONNECTION_INFO = config["CONNECTION_INFO"];
    initializeConnection();
}

Database::~Database()
{
    PQfinish(connection);
}

std::string Database::formatGetDeckCardsQuery(std::string userID, std::string deckID)
{
    std::ostringstream sqlStream;
    sqlStream <<    "SELECT \n"
                        "  \"Card\".\"ID\"\n"
                    "FROM \n"
                        "  public.\"Card\", \n"
                        "  public.\"CardToUser\", \n"
                        "  public.\"CardUserToDeck\", \n"
                        "  public.\"Deck\", \n"
                        "  public.\"DeckToUser\", \n"
                        "  public.\"User\"\n"
                    "WHERE \n"
                        "  \"Card\".\"ID\" = \"CardToUser\".\"CardID\" AND\n"
                        "  \"CardUserToDeck\".\"CardUserID\" = \"CardToUser\".\"ID\" AND\n"
                        "  \"CardUserToDeck\".\"DeckID\" = \"Deck\".\"ID\" AND\n"
                        "  \"Deck\".\"ID\" = \"DeckToUser\".\"DeckID\" AND\n"
                        "  \"DeckToUser\".\"UserID\" = \"User\".\"ID\" AND\n"
                        "  \"User\".\"ID\" = \"CardToUser\".\"UserID\" AND \n"
                        "  \"User\".\"ID\" = " << userID << " AND \"Deck\".\"ID\" = " << deckID << ";";

    return sqlStream.str();
}

void Database::initializeConnection()
{
    connection = PQconnectdb(CONNECTION_INFO.c_str());
    if (PQstatus(connection) != CONNECTION_OK)
    {
        std::cout << "Connection to database failed: " << PQerrorMessage(connection) << std::endl;
    }
    else
    {
        std::cout << "Connected to " << CONNECTION_INFO << std::endl;
    }
}

void Database::initializeConfig()
{
    // Path is relative to the exe in the build folder. This should probably be updated at some point?
    std::ifstream dbfile("../dbconfig.json", std::ifstream::in);
    std::stringstream buffer;
    buffer << dbfile.rdbuf();
    std::string rawJSON = buffer.str();
    config = json::parse(rawJSON);
}
