# [Root-level Dockerfile] - Procedural Programming
# **Purpose:** Instructions to build a Docker container for production or app deployment (prod)

# Original creators (lambda-science/modern-python-boilerplate) used `python:3.13`
FROM python:3.12-slim
COPY --from=ghcr.io/astral-sh/uv:latest /uv /bin/uv

WORKDIR /app
ENV UV_SYSTEM_PYTHON=1
COPY pyproject.toml uv.lock ./
COPY packages/ ./packages/
RUN uv sync --frozen
