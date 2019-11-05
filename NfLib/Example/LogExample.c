#include "Examples.h"
#include <NfLib/Log.h>

void LogExample(void) {
    int i = 0;
    while (1) {
        Log()->Add("%d test\n", i++);
        Log()->Add("%d bla bla...\n", i++);
        Log()->Add(":-D\n");
    }
}
