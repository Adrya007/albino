#init asbweb server application
import os
import logging
import logging.handlers

loggingInitDone = False
if not loggingInitDone:
    loggingInitDone = True

    logger = logging.getLogger('ecosrv')
    logger.setLevel( logging.INFO )

    handlerFile = logging.handlers.RotatingFileHandler( "ecosrv.log", "a", 1024*1024, 5)
    handlerFile.setLevel( logging.INFO )
    handlerFile.setFormatter( logging.Formatter("%(asctime)s %(levelname)s %(name)s - %(message)s") )
    logger.addHandler(handlerFile)

    logger.info("start application")
    
