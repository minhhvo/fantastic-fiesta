from importlib.metadata import entry_points

for plugin in entry_points(group="scripts.plugins"):
    plugin.load()
