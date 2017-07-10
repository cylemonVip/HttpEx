//
//  HTTPManager.cpp
//  HTTPEx
//
//  Created by 程祎 on 2017/7/4.
//
//

#include "HTTPManager.h"

void HTTPManager::getPlayerInfoByID(int id,const httpResponseCallback& callback)
{
    HttpRequest *request = new (std::nothrow) HttpRequest();
    if(request)
    {
        char endStr[100];
        sprintf(endStr, "?type=%d&id=%d", ApiConstant::GET_PLAYER_INFO , id);
        char url[100];
        sprintf(url, "%s%s", HOST, endStr);
        request->setUrl(url);
        request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
        request->setResponseCallback([=](HttpClient* client, HttpResponse* response){
            std::vector<char> *responseData = response->getResponseData();
            std::string responseStr = std::string(responseData->begin(), responseData->end());
            responseStr = filterResponse(responseStr);
            CCLOG("responseStr : %s", responseStr.c_str());
            
            rapidjson::Document document;
            document.Parse<0>(responseStr.c_str());
            callback(document);
        });
        
        std::string data = getJsonData();
        log("data = %s", data.c_str());
        std::vector<std::string> headers;
        
        headers.push_back("Content-Type: application/json; charset=utf-8");
        request->setHeaders(headers);
        
        request->setRequestData(data.c_str(), data.size());
        request->setTag("POST TEST");
        HttpClient::getInstance()->send(request);
        log("url = %s",request->getUrl());
        request->release();
    }else
    {
        request = nullptr;
    }
}

void HTTPManager::setDescription(const std::string description, const ccHttpRequestCallback callback)
{
    HttpRequest *request = new (std::nothrow)HttpRequest();
    
    char endStr[100];
    sprintf(endStr, "?type=%d", ApiConstant::SET_PLAYER_INFO);
    char url[100];
    sprintf(url, "%s%s", HOST, endStr);
    CCLOG("setDescription url = %s", url);
    request->setUrl(url);
    
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    request->setResponseCallback(callback);
    
    std::string data = "";
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("id", 2, allocator);
    document.AddMember("description", rapidjson::Value(description.c_str(), allocator), allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    data = buffer.GetString();
    
    request->setRequestData(data.c_str(), data.size());
    
    HttpClient::getInstance()->send(request);
    
}

std::string HTTPManager::getJsonData()
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("content", 3, allocator);
    
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value object(rapidjson::kObjectType);
    object.AddMember("no", 1, allocator);
    object.AddMember("content", "hello", allocator);
    object.AddMember("state", true, allocator);
    array.PushBack(object, allocator);
    document.AddMember("info", array, allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    return buffer.GetString();
}
