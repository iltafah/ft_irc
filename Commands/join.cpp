#include "Commands.hpp"
#include <vector>

#define NOT_FOUND NULL

std::string Commands::invitedNick;

void Commands::join()
{
    std::string currUserNickname = currUser->getNickName();
    std::vector<std::string> channelNamesList = getNextParam().second;
    std::vector<std::string> channelkeysList = getNextParam().second;
    for (size_t channelIndex = 0; channelIndex < channelNamesList.size(); channelIndex++) {

        currChannel = db->getChannel(channelNamesList[channelIndex]);
        if (currChannel == NOT_FOUND) {

            db->addNewChannel(channelNamesList[channelIndex], currUser);
            sendResponse(fd, ":" + currUserNickname + "!~" + db->getUser(fd)->getUserName() + "@" + _logger.getServerIP() + " JOIN " + channelNamesList[channelIndex] + "\n");
            _logger.ServertoClient(RPL_NAMREPLY(currUserNickname, channelNamesList[channelIndex], "@" + currUserNickname));
            _logger.ServertoClient(RPL_ENDOFNAMES(currUserNickname, channelNamesList[channelIndex]));
        }
        else {

            if (currChannel->getMember(fd) != NULL)
                sendResponse(fd, "User already in channel\n");
            else if (currChannel->getMode('i') == true && currChannel->isUserInvited(currUser->getUserId()) == false)
                _logger.ServertoClient(ERR_INVITEONLYCHAN(currUserNickname, channelNamesList[channelIndex]));
            else if (currChannel->getMode('l') == true && currChannel->getLimit() <= currChannel->getMembers().size())
                _logger.ServertoClient(ERR_CHANNELISFULL(currUserNickname, channelNamesList[channelIndex]));
            else if (currChannel->getMode('k') == true && channelIndex < channelkeysList.size() && currChannel->isKeyMatch(channelkeysList[channelIndex]))
                _logger.ServertoClient(ERR_BADCHANNELKEY(currUserNickname, channelNamesList[channelIndex]));
            else {

                currChannel->addMember(currUser);

                std::string MemberStr;
                std::map<USER_ID, User *> Members = currChannel->getMembers();
                for (std::map<USER_ID, User *>::iterator It_Members = Members.begin(); It_Members != Members.end(); ++It_Members) {
                    if (currChannel->isUserOperator(It_Members->first))
                        MemberStr += "@";
                    MemberStr += It_Members->second->getNickName() + " ";
                }
                SendMessageToMembers(currChannel, currUser, ":" + currUserNickname + "!~" + currUser->getUserName() + "@" + _logger.getServerIP() + " JOIN :" + channelNamesList[channelIndex]);
                _logger.ServertoClient(RPL_NAMREPLY(currUserNickname,channelNamesList[channelIndex],MemberStr)); //how to pranting all list of members on the channel 
            }
        }
    }
}
