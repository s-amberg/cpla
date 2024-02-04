#[====[ Library ]====]

add_library("${CPL_TARGET_WEEK_PREFIX}ex02_type_trivia_lib"
    "lib/Question.cpp"
    "lib/QuestionGenerator.cpp"
    "lib/Trivia.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}ex02_type_trivia_lib" PUBLIC
    "lib"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_type_trivia_lib"
    PUBLIC
    "cpl::boost"
)


#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_type_trivia_app"
    "app/Application.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_type_trivia_app"
    "${CPL_TARGET_WEEK_PREFIX}ex02_type_trivia_lib"
)

