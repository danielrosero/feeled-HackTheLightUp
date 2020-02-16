import pyrebase
from pythonosc import udp_client

config = {
  "apiKey": "AIzaSyAQcvI05cb6U4nCbbsP2YQvRsQ5_b10Nho",
  "authDomain": "lanave-121c6.firebaseapp.com",
  "databaseURL": "https://lanave-121c6.firebaseio.com",
  "storageBucket": "lanave-121c6.appspot.com"
}

def stream_handler(message):
    print(message["event"]) # put
    print(message["path"]) # /-K7yGTTEp7O549EzTYtI
    print(message["data"]) # {'title': 'Pyrebase', "body": "etc..."}

    if message["data"] == 1:
    	print ("Sending OSC to show content")
    	client.send_message("/Content/test/enabled", 1)

    if message["data"] == 0:
    	print ("Sending OSC to hide content")
    	client.send_message("/Content/test/enabled", 0)


firebase = pyrebase.initialize_app(config)
db = firebase.database()

client = udp_client.SimpleUDPClient("127.0.0.1", 2345)



my_stream = db.child("Test/testUser").stream(stream_handler)



# users = db.child("Test/testUser/touch").get()
# print(users.val())


