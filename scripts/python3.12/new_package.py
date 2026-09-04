"""

#!/bin/bash
# Usage: ./scripts/new_package.sh <package_name>
# Note: This script requires admin-granted permission -> run command: chmod +x scripts/new_package.sh

PKG_NAME=$1
if [ -z "$PKG_NAME" ]; then 
  echo "Error: Please provide a package name."
  exit 1
fi

echo "Scaffolding $PKG_NAME..."

# 1. Create the base package directory
mkdir -p "packages/$PKG_NAME"
echo "Package created."

# 2. Prompt for focusing
echo -e "Run Focus Package task?\n(0 == Yes, 1 == No)"
read -r FOCUS_CHOICE

if [ "$FOCUS_CHOICE" = "0" ]; then
  # 3. Prompt for Python setup
  echo -e "Is this a Python package?\n(0 == Yes, 1 == No)"
  read -r PY_CHOICE

  if [ "$PY_CHOICE" = "0" ]; then
    echo "Initializing Python library with uv..."
    uv init --lib "packages/$PKG_NAME"
  fi

  # 4. Trigger the focus script
  echo "Focusing on $PKG_NAME..."
  ./scripts/focus.sh "$PKG_NAME"
fi

"""