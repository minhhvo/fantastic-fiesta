#!/bin/bash
# Stop execution instantly if any command fails
set -e 

echo "=== 1. Compiling (Dev Environment) ==="
ninja -C build
mkdir -p build/reports build/Testing/Temporary
# Grant the 'guest' sandbox user permission to write test logs and XML reports
sudo chmod -R 777 build

echo -e "\n=== 2. Unit Tests (Sandbox Environment) ==="
SANDBOX_ID=$(docker ps -q -f "label=com.docker.compose.service=sandbox" -f "status=running")
if [ -z "$SANDBOX_ID" ]; then
    echo "Error: Could not find a running sandbox container."
    echo "Please run 'Dev Containers: Rebuild' to ensure the background services start."
    exit 1
fi
echo "Connected to Sandbox: $SANDBOX_ID"

echo -e "\n=== 2. Unit Tests (Sandbox Environment) ==="
# Added -f to point to the correct docker-compose location
docker exec "$SANDBOX_ID" ctest --test-dir build \
    -LE "Benchmark" \
    --output-on-failure \
    --output-junit reports/unit_test_report.xml

echo -e "\n=== 3. Micro-Benchmarks (Sandbox Environment) ==="
# Added -f to point to the correct docker-compose location
docker exec "$SANDBOX_ID" ctest --test-dir build \
    -L "Benchmark" \
    --output-on-failure \
    --output-junit reports/benchmark_report.xml

echo -e "\n=== 4. Success ==="
echo "Reports generated at:"
echo "  - build/reports/unit_test_report.xml"
echo "  - build/reports/benchmark_report.xml"

echo -e "\n=== 5. Updating Local GitHub Pages Dashboard ==="
python3 generate_dashboard.py