#include "channel.hpp"
#include "../Users/user.hpp"

# define NOT_FOUND NULL
typedef std::map<USER_ID, User*>::iterator UserIter;

Channel::Channel(User *creator) {

    creator == NULL ? throw std::string("Channel::Channel() -> creator cannot be NULL") : NULL;
    //here I'll have to assign the creator to this channel
    USER_ID creatorId = creator->getUserId();
    //I think it is better to add the creator to both of them
    this->_members[creatorId] = creator;
    this->_operators[creatorId] = creator;
}

void Channel::addMember(User *member) {

    USER_ID memberId = member->getUserId();
    
    member == NULL ? throw std::string("Channel::addMember() -> member cannot be NULL") : NULL;
    getMember(memberId) != NOT_FOUND ? throw std::string("Channel::addMember() -> member already exist") : NULL;

    this->_members[memberId] = member;
}

void Channel::inviteUser(User *user) {

    USER_ID userId = user->getUserId();
    
    user == NULL ? throw std::string("Channel::inviteUser() -> user cannot be NULL") : NULL;
    isUserInvited(userId) == true ? throw std::string("Channel::inviteUser() -> user already invited") : NULL;

    this->_invited[userId] = user;
}

bool Channel::isUserInvited(USER_ID Id) {

    UserIter it = this->_invited.find(Id);
    if (it != this->_invited.end())
        return true;
    return false;
}

bool Channel::isUserOperator(USER_ID Id) {

    UserIter it = this->_operators.find(Id);
    if (it != this->_operators.end())
        return true;
    return false;
}

User* Channel::getMember(USER_ID Id) {

    UserIter it = this->_members.find(Id);
    if (it != this->_members.end())
        return it->second;
    return NULL;
}

Channel::~Channel() {
    
}