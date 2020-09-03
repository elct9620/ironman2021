try:
    import configparser
except ImportError:
    import ConfigParser as configparser

Import("env")

config = configparser.ConfigParser()
config.read("platformio.ini")

script = config.get(f"env:{env['PIOENV']}", "custom_ruby_script")

env.Execute(f"mrbc -B app -o include/app.h {script}")
