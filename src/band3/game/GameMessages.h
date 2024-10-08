#pragma once
#include "obj/Msg.h"

BEGIN_MESSAGE(LocalUserLeftMsg, local_user_left, );
    MESSAGE_ARRAY_CTOR(LocalUserLeftMsg)
END_MESSAGE;

BEGIN_MESSAGE(UserLoginMsg, user_login, );
    MESSAGE_ARRAY_CTOR(UserLoginMsg)
END_MESSAGE;

BEGIN_MESSAGE(AddLocalUserResultMsg, add_local_user_result_msg, );
    MESSAGE_ARRAY_CTOR(AddLocalUserResultMsg)
END_MESSAGE;