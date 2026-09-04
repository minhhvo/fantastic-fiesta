# [Root-level Dockerfile] - Procedural Programming
# **Purpose:** Instructions to build a Docker container for production or app deployment (prod)

FROM python:3.14-bookworm
COPY --from=ghcr.io/astral-sh/uv:latest /uv /bin/uv

WORKDIR /app
ENV UV_SYSTEM_PYTHON=1
COPY pyproject.toml uv.lock ./
COPY packages/ ./packages/
RUN uv sync --frozen
