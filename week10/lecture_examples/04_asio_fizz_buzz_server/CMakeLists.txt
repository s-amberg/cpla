add_executable("${CPL_TARGET_WEEK_PREFIX}04_asio_fizz_buzz_server"
    "FizzBuzz.cpp"
    "FizzBuzzServer.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}04_asio_fizz_buzz_server" PRIVATE
    "Threads::Threads"
    "cpl::asio"
)
