#ifndef UserDto_hpp
#define UserDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
     VALUE(GUEST, 0, "ROLE_GUEST"),
     VALUE(ADMIN, 1, "ROLE_ADMIN")
)

class UserDto : public oatpp::DTO {
  
  DTO_INIT(UserDto, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, userName, "unique-username");
  DTO_FIELD(String, email, "unique@email.com");
  DTO_FIELD(String, password, "password");
  DTO_FIELD(Enum<Role>::AsString, role, "role");
    
  DTO_FIELD(UInt32, userId);
  DTO_FIELD(String, token);
  DTO_FIELD(Boolean, saveImage);
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

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */
