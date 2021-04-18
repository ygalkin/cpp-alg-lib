#include "smart-ptr/test.h"
#include "sort/test.h"
#include "container/test.h"

int main() {
    container::test().run();
    smart_ptr::test().run();
    sort::test().run();
}
