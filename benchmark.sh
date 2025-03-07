#!/bin/bash

echo "=== Running sumpy benchmark ==="
echo "Command: python3 sumpy_run.py"
time python3 sumpy_run.py

echo ""
echo "=== Running numpy benchmark ==="
echo "Command: uv run numpy_run.py"
time uv run numpy_run.py

echo ""
echo "=== Benchmark Complete ===" 