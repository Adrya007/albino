import cStringIO, urllib, Image, gluon.tools

mySudoku = local_import('sudoku')
service = gluon.tools.Service(globals())

def call():
    session.forget()
    return service()

@service.amfrpc3("srv")
def echo(puzzle):
    return mySudoku.solveSudoku(str(puzzle))
