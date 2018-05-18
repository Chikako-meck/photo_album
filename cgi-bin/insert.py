#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import cgi
import sqlite3
import sys, urllib
import urllib2
import os.path

def download(url):
    try:
        # URLから画像を取得
        i = urllib2.urlopen(url)
        filename = url.split('/')[-1]
        # saveData というバイナリデータを作成
        saveData = open('/Users/ChikakoTAKASAKI/Desktop/reason-react-example/images/' + filename, 'w');
        # saveDataに取得した画像を書き込み
        saveData.write(i.read());
        saveData.close()
        print u'>>> get:' + filename
        print "<br>"
        i.close()
    except Exception as e:
        print '=== エラー内容 ==='
        print 'type: ' + str(type(e)) + '\n'
        print 'args: ' + str(e.args) + '\n'
        print 'message: ' + e.message + '\n'
        print 'e: ' + str(e) + '\n'
        print u'>>> error: ' + url + '\n'

db = sqlite3.connect('image.db')
c = db.cursor()
print "content-type: text/html charset=UTF-8\n"

print "<html><head><link rel='stylesheet' href='../src/simple/style.css' type='text/css' /></head><body>"
form = cgi.FieldStorage()
form_check = 0
if form.has_key("date") and form.has_key("category") and form.has_key("filename"):
    form_check = 1
if form_check == 0 :
    print "<h1>ERROR !</h1>"
    print "Please input date, category and image URL.</br>"

else :
    date = form["date"].value
    category = form["category"].value
    filename = form["filename"].value
    path = "/images/" + filename.split('/')[-1]
    c.execute("INSERT INTO image_table VALUES(?,?,?)", [date, category, path])
    db.commit()
    db.close()
    print "<h2>insert data into database</h2><hr>"
    print "<br>"
    download(filename)
    print "SUCCESS!<br/>"
    print "<img src=%s><br/>" % path
index = "location.href='../src/simple/index.html'"
print "<input type='button' onClick=%s value='back'id='back'/>" % index
print "</body></html>"
