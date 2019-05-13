from flask import Flask, render_template,url_for
from bson import ObjectId # For ObjectId to work   
import pymongo
import json
app = Flask(__name__)   
myclient = pymongo.MongoClient("mongodb://localhost:27017/")
mydb = myclient["marwin"]

mycol2 = mydb["mq2"]
mycol3 = mydb["mq3"]
mycol4 = mydb["mq4"]
mycol5 = mydb["mq5"]
mycol6 = mydb["mq6"]
mycol7 = mydb["mq7"]
mycol8 = mydb["mq8"]
mycol9 = mydb["mq9"]

@app.route('/')
def temp():

	doc2 = mycol2.find({},{"_id" : 0 ,"payload": True}).sort([('payload', -1)]).limit(1)
	for x in doc2:
		json_str=json.dumps(x)
		resp=json.loads(json_str)
		mq2=resp['payload']

	doc3 = mycol3.find({},{"_id" : 0 ,"payload": True}).sort([('payload', -1)]).limit(1)
	for x in doc3:
		json_str=json.dumps(x)
		resp=json.loads(json_str)
		mq3=resp['payload']

	doc4 = mycol4.find({},{"_id" : 0 ,"payload": True}).sort([('payload', -1)]).limit(1)
	for x in doc4:
		json_str=json.dumps(x)
		resp=json.loads(json_str)
		mq4=resp['payload']

	doc5 = mycol5.find({},{"_id" : 0 ,"payload": True}).sort([('payload', -1)]).limit(1)
	for x in doc5:
		json_str=json.dumps(x)
		resp=json.loads(json_str)
		mq5=resp['payload']

	doc6 = mycol6.find({},{"_id" : 0 ,"payload": True}).sort([('payload', -1)]).limit(1)
	for x in doc6:
		json_str=json.dumps(x)
		resp=json.loads(json_str)
		mq6=resp['payload']

	doc7 = mycol7.find({},{"_id" : 0 ,"payload": True}).sort([('payload', -1)]).limit(1)
	for x in doc7:
		json_str=json.dumps(x)
		resp=json.loads(json_str)
		mq7=resp['payload']

	doc8 = mycol8.find({},{"_id" : 0 ,"payload": True}).sort([('payload', -1)]).limit(1)
	for x in doc8:
		json_str=json.dumps(x)
		resp=json.loads(json_str)
		mq8=resp['payload']


	doc9 = mycol9.find({},{"_id" : 0 ,"payload": True}).sort([('payload', -1)]).limit(1)
	for x in doc9:
		json_str=json.dumps(x)
		resp=json.loads(json_str)
		mq9=resp['payload']
		return render_template('marwin.html',mq2=mq2,mq3=mq3,mq4=mq4,mq5=mq5,mq6=mq6,mq7=mq7,mq8=mq8,mq9=mq9)

@app.route('/about.html')
def about():
    return render_template('about.html')

#@app.route('/contact.html')
#def contact():
#    return render_template('contact.html')

#@app.route('/index.html')
#def index():
 #   return render_template('index.html')

#@app.route('/gallery.html')
#def gallery():
 #   return render_template('gallery.html')


#@app.route('/hardware.html')
#def hardware():
#    return render_template('hardware.html')


#@app.route('/software.html')
#def software():
 #   return render_template('software.html')




if __name__ == '__main__':
    app.run(debug=True)