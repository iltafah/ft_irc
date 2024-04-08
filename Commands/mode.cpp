#include "Commands.hpp"
#include <cstddef>

//+t not seted at the begining of join
// user does not exist in -o

void Commands::mode()
{
    std::string channelName = getNextParam().first;
    std::string modesStr = getNextParam().first;
    std::string modeArg;

    currChannel = db->getChannel(channelName);

    if (currChannel == NULL)
    {
        _logger.ServertoClient(ERR_NOSUCHCHANNEL(currUser->getNickName(), channelName));
        return;
    }
    else if (currChannel->isUserOperator(currUser->getUserId()) == false)
    {
        _logger.ServertoClient(ERR_CHANOPRIVSNEEDED(db->getUser(fd)->getNickName(), channelName));
        return;
    }
    else if(_paramCounter == 2)
    {
        //i need to get args 
        // _logger.ServertoClient(RPL_CHANNELMODEIS(db->getUser(fd)->getNickName(), channelName, currChannel->getModes(), modearg))
        _logger.ServertoClient(RPL_CHANNELMODEIS(db->getUser(fd)->getNickName(), channelName, currChannel->getModes()));
    }
    else
    {
        puts("0");
        // currChannel->setModes(modesStr);
        char sign = '+'; // by default if no sign is specified within given modeStr
        for (size_t i = 0; i < modesStr.length(); i++)
        {
            puts("1");
            modesStr[i] == '+' ? sign = '+' : (modesStr[i] == '-' ? sign = '-' : sign);

            char currModeLetter = modesStr[i];
            if (currModeLetter == 'i' || currModeLetter == 'k' || currModeLetter == 'l' || currModeLetter == 'o' || currModeLetter == 't')
            {
                puts("2");
                if (sign == '+' && (currChannel->getMode(currModeLetter) == false || currModeLetter == 'k' || currModeLetter == 'o'))
                {
                    puts("3");
                    if (currModeLetter == 'k')
                    {
                        modeArg = getNextParam().first;
                        currChannel->setKey(modeArg);
                    }
                    else if (currModeLetter == 'l')
                    {
                        modeArg = getNextParam().first;
                        size_t limit = static_cast<size_t>(atoi(modeArg.c_str()));
                        currChannel->setLimit(limit > 0 ? limit : 1);
                    }
                    else if(currModeLetter == 'o' && _paramCounter == 3)
                    {
                        _logger.ServertoClient(ERR_SPECIFYPARAM(db->getUser(fd)->getNickName(), channelName));
                        continue;
                    }
                        
                    else if (currModeLetter == 'o' && _paramCounter == 4)
                    {
                        puts("4");
                        modeArg = getNextParam().first;
                        User *Operator = db->existUser(modeArg);
                        if (!Operator)
                        {
                            _logger.ServertoClient(ERR_NOUSERS(db->getUser(fd)->getNickName(), channelName));
                            continue;
                        }
                        else if (currChannel->isNickExist(modeArg) == false)
                        {
                            _logger.ServertoClient(ERR_USERNOTINCHANNEL(currUser->getNickName(), modeArg, channelName));
                            continue;
                        }
                        else
                        {
                            currChannel->addOperator(Operator->getUserId());
                            SendMessageToMembers(currChannel, currUser, "MODE " + channelName + " +o " + modeArg);
                        }
                    }

                    currChannel->setMode(currModeLetter);
                }
                else if (sign == '-' && currChannel->getMode(currModeLetter) == true)
                {
                    if (currModeLetter == 'k')
                    {
                        currChannel->clearKey();
                    }
                    else if(currModeLetter == 'o' && _paramCounter == 3)
                    {
                        _logger.ServertoClient(ERR_SPECIFYPARAM(db->getUser(fd)->getNickName(), channelName));
                        continue;
                    }    
                        
                    else if (currModeLetter == 'o' && _paramCounter == 4)
                    {
                        modeArg = getNextParam().first;
                        User *Operator = db->existUser(modeArg);
                        if (currChannel->isNickExist(modeArg) == false)
                        {
                            _logger.ServertoClient(ERR_USERNOTINCHANNEL(currUser->getNickName(), modeArg, channelName));
                            continue;
                        }
                        else if (!Operator)
                        {
                            _logger.ServertoClient(ERR_NOUSERS(db->getUser(fd)->getNickName(), channelName));
                            continue;
                        }
                        else
                        {
                            if (currChannel->isUserOperator(Operator->getUserId()) == true && currChannel->isUserOperator(currUser->getUserId()) == true)
                            {
                                currChannel->deleteOperator(Operator);
                                SendMessageToMembers(currChannel, currUser, "MODE " + channelName + " -o " + modeArg);
                            }
                        }
                    }
                    currChannel->removeMode(currModeLetter);
                }
            }
        }
    }
}
