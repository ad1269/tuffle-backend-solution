CPP_FILES = $(shell find . -type f -name '*.cc' -o -name '*.h')

TOOL_TARGETS = build test stylecheck formatcheck all check_style_passed

.PHONY: server clean $(TOOL_TARGETS)

server: wordle_backend

wordle_backend: $(CPP_FILES)
	g++ -g -O0 -o wordle_backend dictionary.cc gamestate.cc main.cc tuffle.cc -lpthread -std=c++17

clean:
	rm wordle_backend

tools/output:
	@mkdir -p tools/output

$(TOOL_TARGETS): tools/output
	@$(MAKE) -C tools/cppaudit $(MAKECMDGOALS)
