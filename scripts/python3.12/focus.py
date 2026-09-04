"""
#!/bin/bash
# Usage: ./scripts/focus.sh <package_name>

PKG_NAME=$1
if [ -z "$PKG_NAME" ]; then 
  echo "Error: Please provide a package name."
  exit 1
fi

mkdir -p .vscode

# Inject the lock and the dynamic key
cat << JSON > .vscode/settings.json
{
  "files.readonlyInclude": {
    "packages/**": true
  },
  "files.readonlyExclude": {
    "packages/$PKG_NAME/**": true
  }
}
JSON

echo "Workspace soft-locked. Excluded from Read-only: packages/$PKG_NAME."

"""