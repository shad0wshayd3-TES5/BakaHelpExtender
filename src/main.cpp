#include "ObScript/Help.h"

namespace
{
	void MessageCallback(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type)
		{
		case SKSE::MessagingInterface::kPostLoad:
			ObScript::Help::Install();
			break;
		case SKSE::MessagingInterface::kDataLoaded:
			ObScript::Help::ClearCellMap();
			break;
		default:
			break;
		}
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);
	SKSE::GetMessagingInterface()->RegisterListener(MessageCallback);

	return true;
}
