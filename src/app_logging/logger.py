#AppInstaller/src/logging/logging.py


import logging
from rich.logging import RichHandler

def setup_logger(debug: bool = False):
    """
    Setup the logger for the application.
    
    Args:
        debug (bool): Enable debug mode.

    Returns:
        logging.Logger: The logger for the application. 

    Example:
        >>> logger = setup_logger(debug=True) \\
        >>> logger.info("Hello, World!") \\
        >>> logger.debug("App Debugging!") \\
        >>> logger.warning("App Warning!") \\
        >>> logger.error("App Error!") \\
        >>> logger.critical("App Critical!") \\
    """
    level = logging.DEBUG if debug else logging.INFO

    logging.basicConfig(
        level=level,
        format="%(message)s",
        datefmt="[%X]",
        handlers=[RichHandler(rich_tracebacks=True, markup=True, show_path=True)]
    )

    return logging.getLogger("app")


if __name__ == "__main__":
    logger = setup_logger(debug=True)

    logger.info("Hello, World!")
    logger.debug("App Debugging!")
    logger.warning("App Warning!")
    logger.error("App Error!")
    logger.critical("App Critical!")