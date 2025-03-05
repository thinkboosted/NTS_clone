#!/bin/bash

# Colors for output
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
RESET="\033[0m"

# Default directory
TEST_DIR="./tests"

# Check for command-line argument
if [ $# -ge 1 ]; then
    TEST_DIR="$1"
fi

# Display selected test directory
echo -e "${YELLOW}Using test directory: ${TEST_DIR}${RESET}"

# Check if nanotekspice executable exists
if [ ! -f "./nanotekspice" ]; then
    echo -e "${RED}Error: nanotekspice executable not found${RESET}"
    echo "Make sure to compile the program first with 'make'"
    exit 1
fi

# Find all .nts files in specified directory and subdirectories
echo -e "${YELLOW}Searching for .nts circuit files...${RESET}"
NTS_FILES=$(find "${TEST_DIR}" -type f -name "*.nts" 2>/dev/null)

# Check if any .nts files were found
if [ -z "$NTS_FILES" ]; then
    echo -e "${YELLOW}No .nts files found in ${TEST_DIR}. Please check the directory path.${RESET}"
    exit 0
fi

echo -e "Found $(echo "$NTS_FILES" | wc -l) circuit files to test."
echo -e "${YELLOW}Starting component tests...${RESET}"
echo "=========================================="

PASS_COUNT=0
FAIL_COUNT=0
ERROR_LOG="component_test_errors.log"
> "$ERROR_LOG" # Clear error log

# Test each component file
for file in $NTS_FILES; do
    echo -n "Testing $(basename "$file")... "
    
    # Run nanotekspice with the file and exit immediately
    # Using timeout to prevent hanging
    output=$(timeout 2s ./nanotekspice "$file" <<< "exit" 2>&1)
    exit_code=$?
    
    # Check exit status (0 = success, 124 = timeout, other = crash)
    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}PASS${RESET}"
        ((PASS_COUNT++))
    elif [ $exit_code -eq 124 ]; then
        echo -e "${RED}TIMEOUT${RESET}"
        echo "File: $file - TIMEOUT" >> "$ERROR_LOG"
        echo "Output: $output" >> "$ERROR_LOG"
        ((FAIL_COUNT++))
    else
        echo -e "${RED}CRASH (exit code $exit_code)${RESET}"
        echo "File: $file - EXIT CODE $exit_code" >> "$ERROR_LOG"
        echo "Output: $output" >> "$ERROR_LOG"
        ((FAIL_COUNT++))
    fi
done

# Display summary
echo "=========================================="
echo -e "Test Summary:"
echo -e "  ${GREEN}Passed: $PASS_COUNT${RESET}"
echo -e "  ${RED}Failed: $FAIL_COUNT${RESET}"
echo -e "  Total: $((PASS_COUNT + FAIL_COUNT))"

if [ $FAIL_COUNT -eq 0 ]; then
    echo -e "${GREEN}All components processed successfully!${RESET}"
    exit 0
else
    echo -e "${RED}Some components caused crashes. See $ERROR_LOG for details.${RESET}"
    exit 1
fi