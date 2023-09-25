#ifndef RB3_APP_HPP
#define RB3_APP_HPP

struct App {
	App(int argc, char **argv);
	~App();
	void Run();
	void RunWithoutDebugging();
};
#endif
