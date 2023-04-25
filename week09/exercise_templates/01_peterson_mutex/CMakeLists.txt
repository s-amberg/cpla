#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}01_peterson_mutex_lib" INTERFACE)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}01_peterson_mutex_lib" INTERFACE
    "lib"
)

#[====[ Application ]====]

add_executable("${CPL_TARGET_WEEK_PREFIX}01_peterson_mutex"
    "app/main.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}01_peterson_mutex" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}01_peterson_mutex_lib"
    "Threads::Threads"
)
