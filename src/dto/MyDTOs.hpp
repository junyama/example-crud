
#ifndef MyDTOs_hpp
#define MyDTOs_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
/*
class HelloDto : public oatpp::DTO {
  
  DTO_INIT(HelloDto, DTO)
  
  DTO_FIELD(String, userAgent, "user-agent");
  DTO_FIELD(String, message);
  DTO_FIELD(String, server);
  
};

class MessageDto : public oatpp::DTO {
  
  DTO_INIT(MessageDto, DTO)
  
  DTO_FIELD(String, message);
  
};


class UserAccountObj : public oatpp::DTO {

  DTO_INIT(UserAccountObj, DTO)

  DTO_FIELD(UInt32, userId);
  DTO_FIELD(String, token);
  DTO_FIELD(Boolean, saveImage);
};

class UserAccountListObj : public oatpp::DTO {

  DTO_INIT(UserAccountListObj, DTO)

  DTO_FIELD(List<Object<UserAccountObj>>, userAccountList); 
};

*/

class ServerConfigObj : public oatpp::DTO {

  DTO_INIT(ServerConfigObj, DTO /* extends */)

  DTO_FIELD(Boolean, saveImage);
  DTO_FIELD(List<Object<UserAccountObj>>, userList); 
};

class BoundingBoxObj : public oatpp::DTO {

  DTO_INIT(BoundingBoxObj, DTO /* extends */)

  DTO_FIELD(Int32, sex);
  DTO_FIELD(Int32, score);
  DTO_FIELD(Int32, top);
  DTO_FIELD(Int32, left);
  DTO_FIELD(Int32, height);
  DTO_FIELD(Int32, width);
};

class ImgBoundingBoxObj : public oatpp::DTO {

  DTO_INIT(ImgBoundingBoxObj, DTO /* extends */)

  DTO_FIELD(String, img);
  DTO_FIELD(List<Object<BoundingBoxObj>>, boxList); 
};

#include OATPP_CODEGEN_END(DTO)

#endif /* MyDTOs_hpp */
