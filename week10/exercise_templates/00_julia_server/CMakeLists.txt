#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}00_julia_server_lib"
    "lib/src/bmp.cpp"
    "lib/src/image.cpp"
    "lib/src/julia.cpp"
    "lib/src/remote.cpp"
    "lib/src/server.cpp"
    "lib/src/worker_pool.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}00_julia_server_lib" PUBLIC
    "lib/include"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}00_julia_server_lib" PUBLIC
    "cpl::asio"
    "cpl::simple-http"
)

#[====[ Application ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}00_julia_server"
    "app/main.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}00_julia_server" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}00_julia_server_lib"
    "Threads::Threads"
)
