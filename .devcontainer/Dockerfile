# File: .devcontainer/Dockerfile

# ==============================================================================
# STAGE 1: BASE (Debian Bookworm + Core Execution)
# ==============================================================================
FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12 AS base

# Install Wine for testing Windows cross-compiled binaries
RUN apt-get update && apt-get install -y --no-install-recommends \
    mingw-w64 wine64 \
    && rm -rf /var/lib/apt/lists/*

# Create exact directory structures for physical host bind mounts
RUN mkdir -m 775 -p /clib/msvc /clib/windows_kits /clib/dst

# ==============================================================================
# STAGE 2: DEV ENVIRONMENT (Root User, Full C++/Python Tools)
# ==============================================================================

FROM base AS devcontainer

# Restore uv for Python dependency management
COPY --from=ghcr.io/astral-sh/uv:latest /uv /bin/uv

ENV UV_COMPILE_BYTECODE=1 \
    UV_LINK_MODE=copy \
    UV_NO_CACHE=0

# Configure persistent bash history for the built-in 'vscode' user
RUN mkdir -p /commandhistory \
    && chown -R vscode:vscode /commandhistory \
    && echo "export PROMPT_COMMAND='history -a' && export HISTFILE=/commandhistory/.bash_history" >> /home/vscode/.bashrc

# Switch to the superuser
USER vscode
RUN uv python install
WORKDIR /workspace

# ==============================================================================
# STAGE 3: SANDBOX ENVIRONMENT (Restricted User, Execution Only)
# ==============================================================================
FROM base AS sandbox

# Create a restricted Debian user with zero root privileges
RUN useradd --create-home --shell /bin/bash guest

# Globally lock this container stage to the unprivileged user
USER guest
WORKDIR /sandbox_workspace