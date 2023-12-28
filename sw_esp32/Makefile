CPPCHECK = cppcheck
CPPCHECK_INCLUDES = \
	./plant_boss/inc \
	./plant_boss/drivers \
	./plant_boss/wrappers
IGNORE_FILES_FORMAT_CPPCHECK = \
	external/printf/printf.h \
	external/printf/printf.c
MAIN_FILE = plant_boss/src/main.c
SOURCES_WITH_HEADERS = \
		plant_boss/src/thread_app.c
SOURCES = \
		$(MAIN_FILE) \
		$(SOURCES_WITH_HEADERS)
SOURCES_FORMAT_CPPCHECK = $(filter-out $(IGNORE_FILES_FORMAT_CPPCHECK),$(SOURCES))
HEADERS_FORMAT = $(filter-out $(IGNORE_FILES_FORMAT_CPPCHECK),$(HEADERS))
CPPCHECK_FLAGS = \
	--enable=all \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=unmatchedSuppression \
	--suppress=unusedFunction \
	$(addprefix -I,$(CPPCHECK_INCLUDES)) \

cppcheck:
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SOURCES_FORMAT_CPPCHECK)

cppcheck1:
	cppcheck \
	--enable=all \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=unmatchedSuppression \
	--suppress=unusedFunction \
	-I ./plant_boss/inc \
	-I ./plant_boss/drivers \
	-I ./plant_boss/wrappers \
	plant_boss/drivers/bh1750fvi.c \
	plant_boss/drivers/hw390.c \
	plant_boss/drivers/lm20bim7.c \
	plant_boss/src/thread_app.c \
	plant_boss/src/thread_input.c \
	plant_boss/src/thread_output.c \
	plant_boss/src/thread_network.c \
	plant_boss/src/thread_memory.c