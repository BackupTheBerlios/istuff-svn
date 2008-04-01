import pykeygrab
import keycapture # doesn't seperate key up and key down events
import socket
import select
import struct

OPCODE_DISCONNECT = chr(1)
OPCODE_BACKLIGHT_ON	= chr(2)
OPCODE_BACKLIGHT_OFF = chr(3)
OPCODE_KEY_RECEIVED	= chr(4)
OPCODE_PLAYSOUND = chr(5)
OPCODE_STOPSOUND = chr(6)
OPCODE_LAUNCHAPP = chr(7)
OPCODE_CLOSEAPP = chr(8)
OPCODE_KEY_PRESSED = chr(9)
OPCODE_START_KEYCAPTURE = chr(10)
OPCODE_STOP_KEYCAPTURE = chr(11)
OPCODE_CHANGEPROFILE = chr(12)

# key activity types
KEY_PRESS = 1
KEY_UP = 2
KEY_DOWN = 3

class iStuffMobile:
	def __init__(self, bt_address = None):
		print "in __init__"
		try:
			if(bt_address == None):
				self.address,self.services=socket.bt_discover()
			else:
				self.address,self.services=socket.bt_discover(bt_address)
			print "Discovery successful"
			print self.address
			print self.services
		except:
			import traceback
			import appuifw
			traceback.print_exc()
			appuifw.query(unicode("Error in bluetooth connection, is the service running"), 'query')
			appuifw.app.body.text((40, 90), unicode("Please restart!"))
			lock = e32.Ao_lock()
			lock.wait()
		self.data = ""
		self.sock=0
		self.lock=0
		if len(self.services)>1:
			import appuifw
			choices=self.services.keys()
			choices.sort()
			choice=appuifw.popup_menu([unicode(self.services[x])+": "+x for x in choices],u'Choose port:')
			self.target=(self.address,self.services[choices[choice]])
		else:
			self.target=(self.address,self.services.values()[0])
		self.key_capturer = keycapture.KeyCapturer(self.key_callback)
		self.key_capturer.keys = keycapture.all_keys
			
		
	####################	
	# run
	#	keep processing incoming data from the BT socket
	####################
	def run(self):
		# you must create the socket in the same thread you read from it
		# see the following thread: http://discussion.forum.nokia.com/forum/showthread.php?t=79738   
		self.running = True
	
		if not self.sock:
			address, services = socket.bt_discover(self.address)
			self.sock=socket.socket(socket.AF_BT,socket.SOCK_STREAM)
			print "about to connect to socket"
			self.sock.connect(self.target)
		else:
			print "socket already initialized", self.sock
	
		while self.running == True:
			# await a read event
			rlist, wlist, elist = select.select( [self.sock], [], [], 5)

			# test for timeout
			if [rlist, wlist, elist] == [[], [], []]:
				print "Five seconds elapsed.\n"
			else:
				for sock in rlist:
					data = sock.recv( 100 )
					self.parse_data(data)

		#self.sock.shutdown(2)
		self.sock.close()
		self.sock = 0
		
	####################	
	# parse_data
	#	keep processing incoming data from the BT socket
	####################
	def parse_data(self, data):
		# dictionary used instead of a switch statement
		
		opcode = data[0]
		print "received opcode", ord(opcode)
		try:
			# these functions require no parameters
			{OPCODE_DISCONNECT: self.disconnect,
			 OPCODE_BACKLIGHT_ON: self.backlight_on,
			 OPCODE_BACKLIGHT_OFF: self.backlight_off,
			 OPCODE_STOPSOUND: self.stop_sound,
			 OPCODE_START_KEYCAPTURE: self.start_keycapture,
			 OPCODE_STOP_KEYCAPTURE: self.stop_keycapture,
			}[opcode]()
		except:
			print 'No match for first batch of opcodes'
			
		path = ''
		if(len(data) > 2):
			path_length = data[1]
			path = data[2:] 

		try:
			# these functions require path parameter
			{OPCODE_PLAYSOUND: self.play_sound,
			 OPCODE_LAUNCHAPP: self.launch_app,
			 OPCODE_CLOSEAPP: self.close_app,
			}[opcode](path)
		except:
			print 'No match for second batch of opcodes'
		
		# these functions require path parameter
		if(opcode == OPCODE_KEY_RECEIVED):
			print "key received"
		elif( opcode == OPCODE_CHANGEPROFILE):
			print "change profile received"
			
	def key_callback(self, keycode):
		print "key pressed", keycode
		# '!cHH' = char, unsigned short, unsigned short (see http://docs.python.org/lib/module-struct.html)
		data = struct.pack('!cHH', OPCODE_KEY_PRESSED, keycode, KEY_PRESS)
		print repr(data)
		self.send(data)
		
	def send(self, data):
		if self.sock:
			totalsent = 0
			while totalsent < len(data):
				sent = self.sock.send(data[totalsent:])
				if sent == 0:
					raise RuntimeError, "socket connection broket"
				totalsent = totalsent + sent
						
	def disconnect(self):
		self.running = False
	
	def backlight_on(self):
		print "Backlight On received"
	
	def backlight_off(self):
		print "Backlight Off received"
	
	def stop_sound(self):
		print "stop sound received"
	
	def start_keycapture(self):
		print "start key capture received"
		self.key_capturer.start()
		
	def stop_keycapture(self):
		print "stop key capture received"
		self.key_capturer.stop()
	
	def play_sound(self, path):
		print "play_sound %s" % path
	
	def launch_app(self, path):
		print "launch app %s" % path
		
	def close_app(self, path):
		print "close app %s" % path				
		
def __main__():
	istuff = iStuffMobile()
	istuff.run()