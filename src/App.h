#ifndef HX_APP_H
#define HX_APP_H

class App { public:
    App(int, char**);
    ~App();

    void Run();
    void RunWithoutDebugging();
    void Draw();
    void DrawRegular();
    void CaptureHiRes();
};

#endif // HX_APP_H
