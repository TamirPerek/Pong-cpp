#include "Game.h"

#include <print>
#include <filesystem>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	std::println("argv: {}", argv[0]);
	std::filesystem::current_path(std::filesystem::path{static_cast<std::string>(argv[0])}.parent_path());
	Game tGame;
	return tGame.Start();
}
