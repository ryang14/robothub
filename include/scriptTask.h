#pragma once

#include <Arduino.h>
#include <TeensyThreads.h>

class ScriptTask
{
private:

public:
    volatile static int threadID;
    EXTMEM volatile static char program[100000];
    static Threads::Mutex programLock;

    static void thread();
    static void start() { if(threadID == 0) threadID = threads.addThread(thread); }
    static void stop() { if(threadID > 0) { threads.kill(threadID); threadID = 0; }}
    static void restart() { stop(); start(); }
};
