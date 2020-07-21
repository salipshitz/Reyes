#pragma once

#include "Log.h"

int main(int argc, char **argv) {
	Reyes::Log::Init();
	REY_CORE_WARN("Initialized Core Log");
	REY_LOG_INFO("Initialized Log");

	auto *app = Reyes::CreateApplication();
	app->Run();
	delete app;
}
