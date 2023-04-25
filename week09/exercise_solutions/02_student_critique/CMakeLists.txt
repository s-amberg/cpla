add_executable("${CPL_TARGET_WEEK_PREFIX}sol02_student_critique"
    "main.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}sol02_student_critique" PRIVATE
    "Threads::Threads"
)
