#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "message_suite.h"
#include "mime_type_suite.h"

bool runAllTests(int argc, char const *argv[]) {
	auto xmlfile = cute::xml_file_opener { argc, argv };
	auto listener = cute::xml_listener<cute::ide_listener<>> { xmlfile.out };
	auto const runner = cute::makeRunner(listener, argc, argv);

	cute::suite message_suite = make_suite_message_suite();
	cute::suite mime_type_suite = make_suite_mime_type_suite();
	auto success = runner(message_suite, "message_suite");
	success &= runner(mime_type_suite, "mime_type_suite");
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
