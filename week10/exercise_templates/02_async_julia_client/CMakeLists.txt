#[====[ Application ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}02_async_julia_client"
    "AsyncJuliaClient.cpp"
    "JuliaClient.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}02_async_julia_client" PRIVATE
    "Threads::Threads"
    "cpl::asio"
    "cpl::simple-http"
)
