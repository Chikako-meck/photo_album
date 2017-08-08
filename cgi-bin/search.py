#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cgi
import sqlite3
import sys, urllib
import urllib2
import os.path


db = sqlite3.connect('image.db')
c = db.cursor()
print "content-type: text/html charset=UTF-8\n"

print "<html><head><link rel='stylesheet' href='../src/simple/style.css' type='text/css' /></head><body>"
form = cgi.FieldStorage()
form_check = 0
if form.has_key("keyword_date") and form.has_key("keyword_category"):
    form_check = 1
if form_check == 0 :
    print "<h1>ERROR !</h1>"
    print "Please input keyword date and category.</br>"

else :
    keyword_date = form["keyword_date"].value
    keyword_category = form["keyword_category"].value
    if keyword_date == "1970-01-01":
        c.execute("SELECT * FROM image_table WHERE category = ?", [keyword_category])
    elif keyword_category == "none":
        c.execute("SELECT * FROM image_table WHERE date = ?", [keyword_date])
    else:
        c.execute("SELECT * FROM image_table WHERE date = ? AND category = ?", [keyword_date, keyword_category])
    result = c.fetchall()
    if len(result) == 0:
        print "<h2> Not Found</h2>"
    else:
        print "<h2>==== RESULT ====</h2>"
        print "<table id='history'>"
        print "<tr><td>DATE</td><td>CATEGORY</td><td>IMAGE</td></tr>"
        for row in result:
            print "<tr>"
            print "<td>" + row[0] + "</td>"
            print "<td>" + row[1] + "</td>"
            print "<td><img src=%s></td>" % row[2]
            print "</tr>"
        print "</table>"
    c.close()
    db.close()
index = "location.href='../src/simple/index.html'"
print "<input type='button' onClick=%s value='back'id='back'/>" % index
print "</body></html>"
