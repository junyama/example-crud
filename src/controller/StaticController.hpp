
#ifndef CRUD_STATICCONTROLLER_HPP
#define CRUD_STATICCONTROLLER_HPP

#define USER_ACCOUNT_FILE_PATH "/home/xavier/github/chick-server/conf.d/users.json"
#define IMAGE_FILE_PATH "/home/xavier/github/chick-server/image/"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "dto/MyDTOs.hpp"
#include "halcon/Classifyer.hpp"
#include "halcon/MyDictionary.cpp"

#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

using namespace oatpp::web::server::handler;

class StaticController : public oatpp::web::server::api::ApiController {
private:
    constexpr static const char* TAG = "MyController";
    constexpr static const char* userAcountfilePath = USER_ACCOUNT_FILE_PATH;
    MyDictionary myDictionary;
    oatpp::data::mapping::type::DTOWrapper<UserAccountListObj> userAccountListObj;
    
    static uint miliSecTime() {
        using std::cout; using std::endl;
        using std::chrono::duration_cast;
        using std::chrono::milliseconds;
        using std::chrono::seconds;
        using std::chrono::system_clock;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
    
    oatpp::String getToken(oatpp::data::mapping::type::DTOWrapper<UserAccountListObj> userAccountListObj, UInt32 userId) {
        for (int i = 0; i < userAccountListObj->userAccountList->size(); i++) {
            if (userAccountListObj->userAccountList[i]->userId == userId) {
                OATPP_LOGD(TAG, "userId = %d, token = %s", *userId, userAccountListObj->userAccountList[i]->token->c_str());
                return userAccountListObj->userAccountList[i]->token;
            }
        }
    }
    
    oatpp::data::mapping::type::DTOWrapper<UserAccountObj> getUserAccountObj(oatpp::data::mapping::type::DTOWrapper<UserAccountListObj> userAccountListObj, UInt32 userId) {
        for (int i = 0; i < userAccountListObj->userAccountList->size(); i++) {
            if (userAccountListObj->userAccountList[i]->userId == userId) {
                OATPP_LOGD(TAG, "userId = %d, token = %s", *userId, userAccountListObj->userAccountList[i]->token->c_str());
                return userAccountListObj->userAccountList[i];
            }
        }
    }

public:
  StaticController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {
        auto jsonObjectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        if (oatpp::String jsonStr = oatpp::base::StrBuffer::loadFromFile(userAcountfilePath)) {
            OATPP_LOGD(TAG, "Reading from %s", userAcountfilePath);
            OATPP_LOGD(TAG, "User Account = %s", jsonStr->c_str());
            userAccountListObj = jsonObjectMapper->readFromString<oatpp::Object<UserAccountListObj>>(jsonStr);
        } else OATPP_LOGD(TAG, "%s NOT existing", userAcountfilePath);
        
        setDefaultAuthorizationHandler(std::make_shared<BearerAuthorizationHandler>("my-realm"));
    }
public:

  static std::shared_ptr<StaticController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<StaticController>(objectMapper);
  }

  ENDPOINT("GET", "/", root) {
    const char* html =
      "<html lang='en'>"
      "  <head>"
      "    <meta charset=utf-8/>"
      "  </head>"
      "  <body>"
      "    <p>Hello CRUD example project!</p>"
      "    <a href='swagger/ui'>Checkout Swagger-UI page</a>"
      "  </body>"
      "</html>";
    auto response = createResponse(Status::CODE_200, html);
    response->putHeader(Header::CONTENT_TYPE, "text/html");
    return response;
  }
    
  ENDPOINT("POST", "/detectObject/{userId}", detectObject, BODY_STRING(String, jpegData), PATH(UInt32, userId), AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>, authObject)) {
      OATPP_LOGD(TAG, "token = %s", getToken(userAccountListObj, userId)->c_str());
      //OATPP_ASSERT_HTTP(authObject->token == getToken(userAccountListObj, userId), Status::CODE_401, "Unauthorized");
      auto  usrAccountObj = getUserAccountObj(userAccountListObj, userId);
      OATPP_ASSERT_HTTP(authObject->token == usrAccountObj->token, Status::CODE_401, "Unauthorized");
      
      if (usrAccountObj->saveImage) {
        std::string filePath = IMAGE_FILE_PATH;
        filePath = filePath + std::to_string(*userId) + "-" + std::to_string(miliSecTime()) + ".jpeg";
        jpegData->saveToFile(filePath.c_str());
        OATPP_LOGD(TAG, "an image data has been stored at %s", filePath.c_str());
      }

      try {
          Classifyer *myClassifyer = new Classifyer(&myDictionary);
          myClassifyer -> execute(jpegData->c_str());
          
          auto response = ImgBoundingBoxObj::createShared();
          response->boxList = {};
            if (myClassifyer->boxVector.size() == 0) {
                  auto box = BoundingBoxObj::createShared();
                  box->sex = -1;
                  box->score = 0;
                  box->top = 0;
                  box->left = 0;
                  box->height = 0;
                  box->width = 0;
                  //boxIndex = 0;
                  //OATPP_LOGD(TAG, "{sex:%d,score:%d,position:{top:%d,left:%d,height:%d,width:%d}}", *box->sex, *box->score, *box->top, *box->left, *box->height, *box->width);
                  response->boxList->push_back(box);

            } else {
               for (int boxIndex = 0; boxIndex < myClassifyer->boxVector.size(); ++boxIndex) {
                  auto box = BoundingBoxObj::createShared();
                  box->sex =  myClassifyer->boxVector[boxIndex][0];
                  box->score = myClassifyer->boxVector[boxIndex][1] * 100;
                  box->top = myClassifyer->boxVector[boxIndex][2] * 100;
                  box->left = myClassifyer->boxVector[boxIndex][3] * 100;
                  box->height = myClassifyer->boxVector[boxIndex][4] * 100;
                  box->width = myClassifyer->boxVector[boxIndex][5] * 100;
                  //OATPP_LOGD(TAG, "URI=/chick/%d, boxVector={sex:%5.3f,score:%5.3f,position:{top:%5.3f,left:%5.3f,height:%5.3f,width:%5.3f}}", *deviceId, myClassifyer->boxVector[boxIndex][0], myClassifyer->boxVector[boxIndex][1], myClassifyer->boxVector[boxIndex][2], myClassifyer->boxVector[boxIndex][3], myClassifyer->boxVector[boxIndex][4], myClassifyer->boxVector[boxIndex][5]);
                  OATPP_LOGD(TAG, "BoundingBoxObj={sex:%d,score:%d,position:{top:%d,left:%d,height:%d,width:%d}}", *box->sex, *box->score, *box->top, *box->left, *box->height, *box->width);
                  response->boxList->push_back(box);
                } 
            }
          delete myClassifyer;
          return createDtoResponse(Status::CODE_200, response);
      }
      catch (std::runtime_error e) {
          const char* text = e.what();
          auto response = createResponse(Status::CODE_200, text);
          response->putHeader(Header::CONTENT_TYPE, "text/plane");
          return response;
      }
  }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif //CRUD_STATICCONTROLLER_HPP
