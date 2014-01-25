import gluon.tools
import json

mycalc = local_import('calc')

import logging

service = gluon.tools.Service(globals())

def call():
    session.forget()
    return service()
    
@service.run
def compute():
    year = int(request.vars['year'])
    return json.dumps({"catholic": mycalc.computeCatholic(year), "ortodox": mycalc.computeOrtodox(year)});
        