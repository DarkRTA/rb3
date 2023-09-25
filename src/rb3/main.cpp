#include <rb3/app.hpp>

int main(int argc, char **argv)
{
	App app(argc, argv);
	app.RunWithoutDebugging();
	return 0;
}
