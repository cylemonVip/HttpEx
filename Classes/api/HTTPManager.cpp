//
//  HTTPManager.cpp
//  HTTPEx
//
//  Created by 程祎 on 2017/7/4.
//
//

#include "HTTPManager.h"

HTTPManager* HTTPManager::_instance = nullptr;

HTTPManager* HTTPManager::getInstance()
{
    if(!_instance)
    {
        _instance = new (std::nothrow)HTTPManager();
    }
    
    return _instance;
}

HTTPManager::HTTPManager()
{
    
}

HTTPManager::~HTTPManager()
{
    
}

std::string HTTPManager::filterResponse(std::string response)
{
    CCLOG("filter start length = %lu", response.length());
    //删除报头bom 0xEF 0xBB 0xBF
    if(response.find(0xEF) != std::string::npos)
    {
        response = response.replace(response.find(0xEF), 1, "");
    }
    
    if(response.find(0xBB) != std::string::npos)
    {
        response = response.replace(response.find(0xBB), 1, "");
    }
    
    if(response.find(0xBF) != std::string::npos)
    {
        response = response.replace(response.find(0xBF), 1, "");
    }
    
    CCLOG("filter end length = %lu", response.length());
    return response;
}
