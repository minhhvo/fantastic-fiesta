#!/bin/bash
# Stop execution instantly if any command fails
set -e 

echo "=== 1. Compiling (Dev Environment) ==="
ninja -C build

# Ensure the reports directory exists
mkdir -p build/reports

echo -e "\n=== 2. Unit Tests (Sandbox Environment) ==="
# Added -f to point to the correct docker-compose location
docker compose -f .devcontainer/docker-compose.yml exec sandbox ctest --test-dir build \
    -LE "Benchmark" \
    --output-on-failure \
    --output-junit reports/unit_test_report.xml

echo -e "\n=== 3. Micro-Benchmarks (Sandbox Environment) ==="
# Added -f to point to the correct docker-compose location
docker compose -f .devcontainer/docker-compose.yml exec sandbox ctest --test-dir build \
    -L "Benchmark" \
    --output-on-failure \
    --output-junit reports/benchmark_report.xml

echo -e "\n=== 4. Success ==="
echo "Reports generated at:"
echo "  - build/reports/unit_test_report.xml"
echo "  - build/reports/benchmark_report.xml"