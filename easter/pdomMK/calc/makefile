all:  python-module
	
app: calc.cpp computus.cpp computus.h
	g++ calc.cpp computus.cpp -ocalc -O2 -std=c++11

python-module:
	g++ calc-python.cpp computus.cpp -ocalc.so -shared -O2 -std=c++11 -lboost_python -I/usr/include/python2.7/ -L/usr/lib/python2.7/ -lpython2.7 -fPIC