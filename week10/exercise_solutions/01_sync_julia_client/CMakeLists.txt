#[====[ Application ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}sol01_sync_julia_client"
    "SyncJuliaClient.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol01_sync_julia_client" PRIVATE
    "Threads::Threads"
    "cpl::asio"
    "cpl::simple-http"
)
