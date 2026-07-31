# [#/.devcontainer/Dockerfile] - Procedural Programming
# **Purpose:** Instructions to build a Docker container for development (dev) and code experimenting. 
# *see also:* `./devcontainer.json`.

# Original creators (lambda-science/modern-python-boilerplate) used `python:3.13`
FROM python:3.12-slim-bullseye
COPY --from=ghcr.io/astral-sh/uv:latest /uv /bin/uv

ENV UV_COMPILE_BYTECODE=1
ENV UV_NO_CACHE=1

RUN apt update && \
    apt install -y --no-install-recommends \
    build-essential \
    cmake \
    curl \
    gcc \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspaces/bibtex_frbr