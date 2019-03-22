#######################################################################
# Include the common makefiles:
#   - Variables:     Sets up the variables with some default values
include make_utils/common_variables.mk
#######################################################################

# Project Name
PROJECT_NAME = test_state_machine_example

# Don't run analysis on test code
FLAGS_DONT_ANALYSE = true

# Post build actions (note make -i to ignore errors)
POST_BUILD_TASKS += echo ./state_machine_example_$(TARGET)$(BUILD_SUFFIX);
POST_BUILD_TASKS += cd $(BIN_DIR) && ./state_machine_example_$(TARGET)$(BUILD_SUFFIX);

#######################################################################
# Include the common makefiles:
#   - executable:     Sets the executable file options
#   - warnings:       Set the warning flags for various targets
#   - var_autofill:   Generates lists of source, objects etc
#   - rules:          The build rules
include make_utils/common_executable.mk
include make_utils/common_warnings.mk
include make_utils/common_var_autofill.mk
include make_utils/common_rules.mk

LINK_CMD = @$(ECHO) no linker
#######################################################################
