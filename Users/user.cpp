# include "./user.hpp"
#include <sys/socket.h>
#include "../Channels/channel.hpp"
#include <utility>

typedef std::map<std::string, Channel *>::iterator ChanIter;

bool User::isStrContains(std::string const& str, std::string const& charSet) {

    for (int i = 0; charSet[i]; i++)
        if (str.find(charSet[i]) != std::string::npos) return true;
    return false;
}

bool User::isStrStartWith(std::string const& str, std::string const& charSet) {

    for (int i = 0; charSet[i]; i++)
        if (str.at(0) == charSet[i]) return true;
    return false;
}

User::User(){}

User::User(USER_ID const& Id) : _Id(Id) {
    // _isAuthenticated = false;
    _isPasswordInserted = false;
    _isUserNameInserted = false;
    _isNickInserted = false;
}

USER_ID const& User::getUserId() {
    return (this->_Id);
}

void User::setUserName(USER_NAME const& name) {
    _username = name;
    _isUserNameInserted = true;
}

USER_NAME const & User::getUserName() {
    return (_username);
}

void User::setNickName(NICK_NAME const& name) {
    //welp I think I'll have to check if name is empty, I need to test it
    isStrStartWith(name, "$:#&+~%") == true ? throw  std::string("uWu nickname is wrong") : NULL;
    isStrContains(name, " ,*?!@.") == true ? throw std::string("uWu nickname is wrong") : NULL;
    _nickname = name;
    // std::transform(_nickname.begin(), _nickname.end(), _nickname.begin(), ::toupper);
    _isNickInserted = true;
}

NICK_NAME const & User::getNickName() {
    // std::cout << "NIIIIIII " << _nickname << std::endl;
    return (_nickname);
}


//by agoumi
// void User::SetAuthenticated()
// {
//     if (_UserCheck == true && _NickCheck == true && _Correct_Password == true)
//         _isAuthenticated = true;
// }

bool User::isAuthenticated()
{
    return (_isPasswordInserted == true && _isNickInserted == true && _isUserNameInserted == true);
}

//checking if the pass word are entred and correct
void User::insertedPassSuccessfully()
{
    _isPasswordInserted = true;
}

bool User::hasInsertedPass()
{
    return (_isPasswordInserted);
}

//checking fo entring NickName
// void User::NickCheck()
// {
//     _NickCheck = true;
// }

bool User::hasInsertedNick()
{
    return (_isNickInserted);
}

//checking fo entring NickName
// void User::UserCheck()
// {
//     _UserCheck = true;
// }

bool User::hasInsertedUsername()
{
    return (_isUserNameInserted);
}

void User::joinedChannel(Channel* channel) {
    _joinedChannels.insert(std::make_pair(channel->getChannelName(), channel));
}

void User::partedChannel(Channel* channel) {
    ChanIter it = _joinedChannels.find(channel->getChannelName());
    if (it != _joinedChannels.end())
        _joinedChannels.erase(it);
}

std::map<std::string, Channel *> const& User::getJoinedChannels() {
    return this->_joinedChannels;
}

void User::appendToCmdLine(CND_LINE const &bufferToAppend) {
   this->_cmdLine += bufferToAppend;
}

CND_LINE const& User::getCmdLine() {
    return _cmdLine;
}

void User::clearCmdLine() {
    _cmdLine.clear();
}


// void User::setServerIP(std::string const &ServerIP) //this is not called anywhere
// {
//     // std::cout << _IPServer << std::endl;
//     _IPServer = ServerIP;
// }

// std::string const &User::getServerIP()  //you will get an empty string sing it is not being set
// {
//     // std::cout << _IPServer << std::endl;
//     return (_IPServer);
// }

// //Sending Message to clients
// void User::IRCPrint(size_t fd, std::string string)
// {
//     std::string buffer = string + "\r\n";
//     //catch erro
//     if (send(fd, buffer.c_str(), buffer.length(), 0) < 0)
//         throw std::runtime_error("Error On Sending a Message to the Client.\n");
// }

// void User::ServertoClient(std::string string)
// {
//     IRCPrint(_Id, ":" + GetIpAddress() + " " + string);
// }

// //Send Client To Client
// void    User::CleintToClient(int id, std::string msg)
// {
//     std::string mess = ": " + getNickName() + "!" + getUserName() + "@" + getServerIP() + " " + msg;

//     IRCPrint(id, mess);
// }

//getHostIp Address Again
// std::string User::GetIpAddress()
// {

// 	std::string GetIP;
// 	/*std::istringstream string(*/std::system("ifconfig | grep 'inet ' | awk 'NR==2 {print $2}' > .log")/*)*/;
// 	std::fstream OpenIpFile;
// 	OpenIpFile.open(".log");
// 	std::getline(OpenIpFile, GetIP);
// 	std::system("rm -rf .log");
// 	return GetIP;
// }


User::~User() {
    //here I think I'll have to ... nothing srsly
}
