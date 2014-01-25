#!/usr/bin/env python
# -*- coding: utf-8 -*-

import urllib2
import json

url = 'http://127.0.0.1:8000/app/run/compute?year=2012';

req = urllib2.urlopen(url)

print req.read()