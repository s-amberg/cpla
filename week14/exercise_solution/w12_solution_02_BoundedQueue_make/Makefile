OBJECTS = bounded_queue_heap_memory_suite.o bounded_queue_student_suite.o bounded_queue_single_threaded_lock_suite.o bounded_queue_semantic_suite.o bounded_queue_multi_threaded_suite.o bounded_queue_default_behavior_suite.o Test.o bounded_queue_signatures_suite.o bounded_queue_content_suite.o bounded_queue_non_default_constructible_element_type_suite.o

all: BoundedQueueTests

BoundedQueueTests: $(OBJECTS)
	g++ -o BoundedQueueTests $^ -lpthread

%.o: %.cpp
	g++ -Icute -std=c++17 -c $<
