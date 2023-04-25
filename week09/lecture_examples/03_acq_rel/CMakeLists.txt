add_executable("${CPL_TARGET_WEEK_PREFIX}03_acq_rel"
    "AcqRel.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}03_acq_rel" PRIVATE
    "Threads::Threads"
)
