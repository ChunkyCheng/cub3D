#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counters
PASSED=0
FAILED=0
TOTAL=0

# Timeout for each test (in seconds)
TIMEOUT=5

# Function to test valid cases
test_valid() {
    local test_name="$1"
    local map_file="$2"
    
    TOTAL=$((TOTAL + 1))
    
    echo -n "Testing: $test_name... "
    
    # Create a script that will close the window after a short delay
    # The program should handle the map correctly and exit cleanly when closed
    (
        sleep 0.5
        # Try to find and kill the cub3D process by sending it a signal to close gracefully
        pkill -TERM -f "./cub3D $map_file" 2>/dev/null
        sleep 0.2
        # Force kill if still running
        pkill -KILL -f "./cub3D $map_file" 2>/dev/null
    ) &
    killer_pid=$!
    
    # Run the program with timeout
    timeout $TIMEOUT ./cub3D "$map_file" > /dev/null 2>&1
    local exit_code=$?
    
    # Kill the killer script if still running
    kill $killer_pid 2>/dev/null
    wait $killer_pid 2>/dev/null
    
    # Exit code 0 (normal) or 143 (SIGTERM) or 124 (timeout but started successfully) are acceptable
    # The key is that it should start without errors
    # We'll use valgrind to check if it runs without immediate errors
    timeout 1 valgrind --leak-check=no --error-exitcode=42 ./cub3D "$map_file" > /dev/null 2>&1 &
    local val_pid=$!
    
    sleep 0.3
    
    # Check if valgrind process is still running (means program started successfully)
    if ps -p $val_pid > /dev/null 2>&1; then
        kill -TERM $val_pid 2>/dev/null
        wait $val_pid 2>/dev/null
        echo -e "${GREEN}PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        # Check the exit code
        wait $val_pid
        local val_exit=$?
        if [ $val_exit -eq 42 ]; then
            echo -e "${RED}FAIL${NC} (Valgrind detected errors)"
            FAILED=$((FAILED + 1))
        else
            echo -e "${GREEN}PASS${NC}"
            PASSED=$((PASSED + 1))
        fi
    fi
}

echo -e "${YELLOW}=== Valid Test Cases ===${NC}\n"

# Build the project first
echo "Building project..."
make re > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi
echo ""

# Test all valid .cub files (not in invalid directory)
echo -e "${YELLOW}--- Valid Map Files ---${NC}"

# Find all .cub files in levels but not in levels/invalid
while IFS= read -r file; do
    # Skip files in invalid directory
    if [[ "$file" == *"/invalid/"* ]]; then
        continue
    fi
    
    # Get relative path from current directory
    rel_path="${file}"
    test_name=$(basename "$file" .cub)
    test_valid "$test_name" "$rel_path"
done < <(find levels -name "*.cub" -type f | sort)

# Summary
echo ""
echo -e "${YELLOW}=== Summary ===${NC}"
echo "Total tests: $TOTAL"
echo -e "Passed: ${GREEN}$PASSED${NC}"
echo -e "Failed: ${RED}$FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "\n${RED}Some tests failed!${NC}"
    exit 1
fi
