#include "CallCenter.h"

#include "models/User.h"
#include "utils/UserSimulation.h"

UserSimulation::UserSimulation(std::shared_ptr<CallCenter> center)
    : callCenter(std::move(center))
{
}

void UserSimulation::onRegisterCall(IdType callId, std::string phone)
{
    const auto user = users.emplace(callId, User(callId, std::move(phone), callCenter));
    user.first->second.wait();
}

void UserSimulation::onResponse(IdType callId)
{
    User& user = users.at(callId);
    user.response();
}

void UserSimulation::onEndCall(IdType callId)
{
    users.erase(callId);
}