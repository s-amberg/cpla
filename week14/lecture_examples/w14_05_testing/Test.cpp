#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "answer.h"

void test_answer_is_fourty_two() {
    ASSERT_EQUAL(42, give_me_the_answer());
}

int main(int argc, char const * argv[]) {
    cute::xml_file_opener xmlfile(argc, argv);
    cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
    cute::suite suite{};

    suite.push_back(CUTE(test_answer_is_fourty_two));

    return !cute::makeRunner(lis,argc,argv)(suite);
}

#include "message.h"

#include "chat/message.h"