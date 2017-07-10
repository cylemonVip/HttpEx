//
//  HTTPManager.h
//  HTTPEx
//
//  Created by 程祎 on 2017/7/4.
//
//

#ifndef HTTPManager_h
#define HTTPManager_h

#include <stdio.h>
#include "cocos2d.h"
#include <network/HttpClient.h>
#include <json/rapidjson.h>
#include <json/writer.h>
#include <json/document.h>
#include <json/stringbuffer.h>
#include "ApiConstant.h"

using namespace cocos2d;
using namespace network;

typedef std::function<void(rapidjson::Document&)> httpResponseCallback;

#define HOST "http://bxu2713950036.my3w.com/api/"

struct StudentInfo {
public:
    int id;
    std::string name;
    int age;
    std::string gender;
    std::string description;
    StudentInfo()
    :id(0)
    ,name("")
    ,age(0)
    ,gender("")
    ,description("")
    {
        
    }
};

class HTTPManager {
public:
    HTTPManager();
    ~HTTPManager();
    
    std::string getJsonData();
    void getPlayerInfoByID(int id,const httpResponseCallback& callback);
    void setDescription(const std::string description, const ccHttpRequestCallback callback);
    
    std::string filterResponse(std::string response);
    
private:
    static HTTPManager *_instance;
    
public:
    static HTTPManager* getInstance();
    
};

#endif /* HTTPManager_h */
