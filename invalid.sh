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

# Function to test invalid cases
test_invalid() {
    local test_name="$1"
    shift
    local args="$@"
    
    TOTAL=$((TOTAL + 1))
    
    echo -n "Testing: $test_name... "
    
    # Run the program and capture exit code
    timeout 2 $args > /dev/null 2>&1
    local exit_code=$?
    
    # Check if it failed (non-zero exit code or timeout)
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}FAIL${NC} (Expected error but got success)"
        FAILED=$((FAILED + 1))
    fi
}

# Function to test with backup/restore of header for texture tests
test_invalid_texture() {
    local test_name="$1"
    local map_file="$2"
    local backup_file="HEADERS/parsing.h.backup"
    
    TOTAL=$((TOTAL + 1))
    
    echo -n "Testing: $test_name... "
    
    # Backup original header
    cp HEADERS/parsing.h "$backup_file"
    
    # Modify the header with invalid path
    sed -i 's|textures/coin_animation/coin0.xpm|textures/INVALID_PATH.xpm|g' HEADERS/parsing.h
    
    # Rebuild
    make re > /dev/null 2>&1
    
    # Run the program
    timeout 2 ./cub3D "$map_file" > /dev/null 2>&1
    local exit_code=$?
    
    # Restore original header
    mv "$backup_file" HEADERS/parsing.h
    
    # Rebuild again
    make re > /dev/null 2>&1
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}FAIL${NC} (Expected error but got success)"
        FAILED=$((FAILED + 1))
    fi
}

echo -e "${YELLOW}=== Invalid Test Cases ===${NC}\n"

# Test invalid arguments
echo -e "${YELLOW}--- Argument Tests ---${NC}"
test_invalid "No arguments" ./cub3D
test_invalid "Too many arguments" ./cub3D levels/42.cub extra_arg
test_invalid "Invalid file extension" ./cub3D levels/42.txt
test_invalid "Non-existent file" ./cub3D levels/nonexistent.cub
test_invalid "Directory instead of file" ./cub3D levels/
test_invalid "Empty filename" ./cub3D ""
test_invalid "Relative hidden file named .cub" ./cub3D levels/.cub

echo ""

# Test all files in levels/invalid
echo -e "${YELLOW}--- Invalid Map Files ---${NC}"

# Find all .cub files in levels/invalid
while IFS= read -r file; do
    # Get relative path from current directory
    rel_path="${file}"
    test_name=$(basename "$file" .cub)
    test_invalid "$test_name" ./cub3D "$rel_path"
done < <(find levels/invalid -name "*.cub" -type f | sort)

echo ""

# Test invalid texture paths for maps with coins
echo -e "${YELLOW}--- Invalid Texture Paths ---${NC}"
if [ -f "levels/128-coins.cub" ]; then
    test_invalid_texture "Invalid COIN texture path" "levels/128-coins.cub"
fi

# Test invalid texture paths for maps with doors
if [ -f "levels/door-chains.cub" ]; then
    TOTAL=$((TOTAL + 1))
    echo -n "Testing: Invalid DOOR texture path... "
    
    # Backup original header
    cp HEADERS/parsing.h HEADERS/parsing.h.backup
    
    # Modify the header with invalid door path
    sed -i 's|textures/BrickWall-cracked.xpm|textures/INVALID_DOOR.xpm|g' HEADERS/parsing.h
    
    # Rebuild
    make re > /dev/null 2>&1
    
    # Run the program
    timeout 2 ./cub3D levels/door-chains.cub > /dev/null 2>&1
    exit_code=$?
    
    # Restore original header
    mv HEADERS/parsing.h.backup HEADERS/parsing.h
    
    # Rebuild again
    make re > /dev/null 2>&1
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}FAIL${NC} (Expected error but got success)"
        FAILED=$((FAILED + 1))
    fi
fi

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
