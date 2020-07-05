#include <Arduino.h>
#include <TeensyThreads.h>
#include "scriptTask.h"
#include "my_basic.h"
#include "ports.h"

volatile int ScriptTask::threadID;
EXTMEM volatile char ScriptTask::program[100000];
Threads::Mutex ScriptTask::programLock;

int basprintf(const char *format, ...)
{
    char *buf = (char *)malloc(128);

    va_list ap;
    va_start(ap, format);
    vsnprintf(buf, 128, format, ap);
    for (char *p = &buf[0]; *p; p++) // emulate cooked mode for newlines
    {
        if (*p == '\n')
            Serial.write('\r');
        Serial.write(*p);
    }
    va_end(ap);
    free(buf);
}

void ScriptTask::thread()
{
    struct mb_interpreter_t *bas = NULL;

    mb_init();
    mb_open(&bas);
    mb_set_printer(bas, basprintf);

    programLock.lock();
    mb_load_string(bas, (const char *)program, true);
    programLock.unlock();
    mb_run(bas, true);

    mb_close(&bas);
    mb_dispose();
    threadID = 0;
}