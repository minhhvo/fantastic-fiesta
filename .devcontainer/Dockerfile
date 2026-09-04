# [#/.devcontainer/Dockerfile] - Procedural Programming
# **Purpose:** Instructions to build a Docker container for development (dev) and code experimenting. 
# *see also:* `./devcontainer.json`.


FROM python:3.14-bookworm
COPY --from=ghcr.io/astral-sh/uv:latest /uv /bin/uv

ENV UV_COMPILE_BYTECODE=1 \
    UV_LINK_MODE=copy \
    UV_NO_CACHE=0

RUN apt update && \
    apt install -y --no-install-recommends \
    build-essential \
    cmake \
    curl \
    git \
    ninja-build \
    gdb \
    clangd \
    clang-format \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir /commandhistory
RUN SNIPPET="export PROMPT_COMMAND='history -a' && export HISTFILE=/commandhistory/.bash_history" \
    && echo "$SNIPPET" >> "/root/.bashrc"

WORKDIR /workspaces/projects