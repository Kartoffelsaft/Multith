#pragma once

struct StateHandler
{
public:
    void close() {running = false;}
    bool isRunning() {return running;}
private:
    bool running{true};
};
