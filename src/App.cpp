#include "App.h"
#include "os/Debug.h"

App::~App() {
    TheDebug.Exit(0, true);
}

void App::Run() { RunWithoutDebugging(); }
void App::RunWithoutDebugging() {
    
}
