import os, sys
from logbook import Logger, StreamHandler

StreamHandler(sys.stdout).push_application()

class Log:
    def __init__(self, file: None | str = None) -> None:
        if file:
            file = os.path.basename(file)
        self.log = Logger(file)

    def info(self, msg):
        self.log.info("\033[1;32;40m{}\033[0m".format(msg))

    def warn(self, msg):
        self.log.warn("\033[1;33;40m{}\033[0m".format(msg))

    def err(self, msg):
        self.log.error("\033[1;31;40m{}\033[0m".format(msg))
