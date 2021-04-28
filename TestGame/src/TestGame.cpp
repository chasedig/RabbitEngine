#include <Engine.h>

using namespace RBT;

int main()
{
	Window* window = new Window("TestGame", 1080, 640);
	Engine* engine = new Engine(window);
	window->Run();
}