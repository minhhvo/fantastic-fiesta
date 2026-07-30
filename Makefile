.PHONY: check format type test cov allci

check:
	uv run ruff check .

format:
	uv run ruff format .

type:
	uv run ty

test:
	uv run pytest

cov:
	uv run pytest --cov=packages

allci: format check type cov
