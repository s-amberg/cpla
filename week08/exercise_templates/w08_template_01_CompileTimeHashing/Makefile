.PHONY = all clean

CXX      = g++
CXXFLAGS = -Os -std=c++17 -pedantic-errors

ODMP      = objdump
ODMPFLAGS = -s -j .rdata -j .data

STRS = strings
GREP = grep

PASS = MySuperSecurePassword
HASH = 06196032580217052bad1df90ddd482deeb3387c851fee7af706a314aaf60f6d

all: objdump search_pass search_hash;

clean:
	@rm -f compile_time
	@rm -f runtime



objdump: compile_time runtime
	@echo "Dumping data sections of 'compile_time'"
	@echo "=============================================================================="
	@$(ODMP) $(ODMPFLAGS) compile_time.exe
	@echo "=============================================================================="
	@echo
	@echo "Dumping data sections of 'runtime'"
	@echo "=============================================================================="
	@$(ODMP) $(ODMPFLAGS) runtime.exe
	@echo "=============================================================================="
	@echo

search_pass: compile_time runtime
	@echo "Searching for password in 'compile_time'"
	@echo "=============================================================================="
	@$(STRS) compile_time.exe | $(GREP) $(PASS) || echo "Password not found"
	@echo "=============================================================================="
	@echo
	@echo "Searching for password in 'runtime'"
	@echo "=============================================================================="
	@$(STRS) runtime.exe | $(GREP) $(PASS) || echo "Password not found"
	@echo "=============================================================================="
	@echo

search_hash: compile_time runtime
	@echo "Searching for hash in 'compile_time'"
	@echo "=============================================================================="
	@echo -n "searching for hash in 'compile_time'... "
	@$(STRS) compile_time.exe | $(GREP) $(HASH) || echo "Hash not found"
	@echo "=============================================================================="
	@echo
	@echo "Searching for hash in 'runtime'"
	@echo "=============================================================================="
	@$(STRS) runtime.exe | $(GREP) $(HASH) || echo "Hash not found"
	@echo "=============================================================================="
	@echo

%: %.cpp
	@echo CXX $^
	@$(CXX) $^ $(CXXFLAGS) $(OUTPUT_OPTION)
