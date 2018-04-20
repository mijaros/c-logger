#include "logger.h"

int main(void)
{
    LOGF_EMERG("Some strange error occured\n");
    LOGF_EMERG("Some error message with \"%s\" and %d\n", "The answer is", 42);
    LOGF_INFO("Some message with lower severity %d\n", 12);
    return 0;
}
