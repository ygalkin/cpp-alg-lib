#include "smart-ptr/test.h"
#include "sort/test.h"
#include "container/test.h"

int main() {
    smart_ptr::test().run();
    container::test().run();
    sort::test().run();
}
