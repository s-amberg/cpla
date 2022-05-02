cmake_minimum_required(VERSION 3.19)

project(w09 LANGUAGES CXX)

find_package("Threads")

# Lecture Examples
week_executable(NAME "non_atomic_flipper"
    SOURCES
    lecture_examples/w09_00_NonAtomicFlipper/NonAtomicFlipper.cpp
    LIBRARIES
    "Threads::Threads"
)

week_executable(NAME "atomic_flat"
    SOURCES
    lecture_examples/w09_01_AtomicFlag/AtomicFlag.cpp
    LIBRARIES
    "Threads::Threads"
)

week_executable(NAME "seq_cst"
    SOURCES
    lecture_examples/w09_02_SeqCst/SeqCst.cpp
    LIBRARIES
    "Threads::Threads"
)

week_executable(NAME "acq_rel"
    SOURCES
    lecture_examples/w09_03_AcqRel/AcqRel.cpp
    LIBRARIES
    "Threads::Threads"
)

week_executable(NAME "relaxed"
    SOURCES
    lecture_examples/w09_04_RelaxedMemoryOrder/RelaxedMemoryOrder.cpp
    LIBRARIES
    "Threads::Threads"
)

week_executable(NAME "custom_types"
    SOURCES
    lecture_examples/w09_05_CustomTypes/CustomTypes.cpp
    LIBRARIES
    "Threads::Threads"
)

#Exercise Templates

week_executable(NAME "peterson_mutex"
    SOURCES
    exercise_templates/w09_template_01_PetersonMutex/PetersonMain.cpp
    LIBRARIES
    "Threads::Threads"
)

week_executable(NAME "threadpool"
    SOURCES
    exercise_templates/w09_template_02_StudentCritique/Threadpool.cpp
    LIBRARIES
    "Threads::Threads"
)

# #Exercise Solutions

week_executable(NAME "peterson_mutex_solution"
    SOURCES
    exercise_solution/w09_solution_01_PetersonMutex/PetersonMain.cpp
    LIBRARIES
    "Threads::Threads"
)

week_executable(NAME "threadpool_solution"
    SOURCES
    exercise_solution/w09_solution_02_StudentCritique/Threadpool.cpp
    LIBRARIES
    "Threads::Threads"
)

