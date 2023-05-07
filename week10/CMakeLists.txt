set(CPL_TARGET_WEEK_PREFIX "w10_")

find_package("Threads")

add_subdirectory("lecture_examples/01_asio_resolver")
add_subdirectory("lecture_examples/02_asio_get_request")
add_subdirectory("lecture_examples/03_asio_sync_echo_server")
add_subdirectory("lecture_examples/04_asio_fizz_buzz_server")
add_subdirectory("lecture_examples/05_asio_signals")
add_subdirectory("lecture_examples/06_multi_run")

add_subdirectory("exercise_templates/00_julia_server")
add_subdirectory("exercise_templates/01_sync_julia_client")
add_subdirectory("exercise_templates/02_async_julia_client")

add_subdirectory("exercise_solutions/01_sync_julia_client")
add_subdirectory("exercise_solutions/02_async_julia_client")
