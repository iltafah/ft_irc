#include "database.hpp"

Database *Database::database_ = NULL;

typedef std::map<std::string, Channel *>::iterator ChannelIter;
typedef std::map<USER_ID, User *>::iterator UserIter;
#define NOT_FOUND NULL

void Database::sendResponse(int fd, std::string message)
{
    send(fd, message.c_str(), message.length(), 0);
}

Database::Database()
{
}

Database *Database::GetInstance()
{
    if (database_ == NULL)
    {
        database_ = new Database();
    }
    return database_;
}

User *Database::addNewUser(User *user)
{
    USER_ID userId = user->getUserId();

    user == NULL ? throw std::string("db->addNewUser() -> user cannot be NULL") : NULL;
    getUser(userId) != NOT_FOUND ? throw std::string("db->addNewUser() -> user already exist") : NULL;
    this->_users[userId] = user;
    return user;
}

Channel *Database::addNewChannel(CHANNEL_NAME name, User *user)
{
    Channel *createdChannel;
    user == NULL ? throw std::string("db->addNewChannel() -> user cannot be NULL") : NULL;
    // since the channel take a user in its constructor, it has to assign that user as its operator
    if (getChannel(name) != NOT_FOUND)
        sendResponse(user->getUserId(), "Channel already exists");
    else
    {
        createdChannel = new Channel(name, user);
        this->_channels[name] = createdChannel;
    }

    // user->joinChannel(createdChannel);//srsly I see no need for this, at least for now
    return createdChannel;
}

User *Database::getUser(USER_ID Id)
{

    UserIter it = this->_users.find(Id);
    if (it != this->_users.end())
        return it->second;
    return NULL;
}

Channel *Database::getChannel(CHANNEL_NAME name)
{

    ChannelIter it = this->_channels.find(name);
    if (it != this->_channels.end())
        return it->second;
    return NULL;
}

void Database::deleteUser(USER_ID Id)
{
    UserIter it = this->_users.find(Id);
    free(it->second);
    this->_users.erase(it);
}

void Database::deleteChannel(CHANNEL_NAME name)
{
    ChannelIter it = this->_channels.find(name);
    free(it->second);
    this->_channels.erase(it);
}

// std::vector<std::string> getChannelsName
// added from me