import Tkinter as tk
import subprocess
import os
import tweepy # https://github.com/tweepy/tweepy # twitter-python api for getting tweets
import re # reg-ex for cleaning
import time

#########################################################
#########################################################
#########################################################

class App(tk.Frame):

	def __init__(self, master):
		self.file_name = ""
		self.twitter_handle = ""
		self.num_tweets = 0
		self.markovOrder = 0

		tk.Frame.__init__(self, master)
		self.pack()

		input_frame = tk.Frame(self)
		input_frame.pack(padx=10, pady=20)

		button_frame1 = tk.Frame(self)
		button_frame1.pack(padx=30, pady=15)

		button_frame2 = tk.Frame(self)
		button_frame2.pack(padx=30, pady=10)

		text_frame1 = tk.Frame(self)
		text_frame1.pack(padx=20, pady=20)

		self.master.title("Random Tweet Generator")
		self.master.tk_setPalette(background='#e6e6e6') # works

		self.file_dest_input = tk.Entry(input_frame, width=40, bg="#ececec")
		self.file_dest_label = tk.Label(input_frame, width=20, text="File Destination:")
		self.file_dest_error = tk.Label(input_frame, width=30, bg="#e6e6e6", text="")
		self.file_dest_error.grid(row=0,column=1)
		self.file_dest_input.grid(row=1,column=1)
		self.file_dest_label.grid(row=1,column=0)
		self.file_dest_input.focus_set()

		self.twitter_hand_input = tk.Entry(input_frame, width=40, bg="#ececec")
		self.twitter_hand_label = tk.Label(input_frame, width=20, text="Twitter Handle:")
		self.twitter_hand_error = tk.Label(input_frame, width=30, bg="#e6e6e6", text="")
		self.twitter_hand_error.grid(row=2,column=1)
		self.twitter_hand_input.grid(row=3,column=1)
		self.twitter_hand_label.grid(row=3,column=0)

		self.num_tweets_input = tk.Entry(input_frame, width=40, bg="#ececec")
		self.num_tweets_label = tk.Label(input_frame, width=20, text="# Tweets to collect:")
		self.num_tweets_error = tk.Label(input_frame, width=30, bg="#e6e6e6", text="")
		self.num_tweets_error.grid(row=4,column=1)
		self.num_tweets_input.grid(row=5,column=1)
		self.num_tweets_label.grid(row=5,column=0)

		self.master.config(menu= tk.Menu(self.master))

		self.train_program_button = tk.Button(button_frame1, text="Train Program", state='disabled', default='active', command=self.train_program)
		self.get_tweets_button = tk.Button(button_frame1, text="Get Tweets", state='normal', default='active', command=self.get_tweets)
		self.train_program_button.pack(side='right')
		self.get_tweets_button.pack(side='right')

		self.generate_tweet_button = tk.Button(button_frame2, text="Generate Tweet", state='disabled', default='active', command=self.generate_tweet)
		self.generate_tweet_button.pack()

		self.generated_tweet_text = tk.Message(text_frame1, bg='#ececec', text="No Tweets Generated Yet...", relief="groove", width=500)
		# self.generated_tweet_text.config(width=75)
		print(self.generated_tweet_text.config())
		self.generated_tweet_text.pack()

	def get_tweets(self):
		count = 0
		file_input = self.file_dest_input.get()
		if file_input == "" or os.path.exists(file_input) == False:
			self.file_dest_error['bg'] = "red"
			self.file_dest_error['text'] = "Enter a valid file destination!"
		else:
			self.file_dest_error['bg'] = "#e6e6e6"
			self.file_dest_error['text'] = ""
			count += 1
		#########################################################
		#Twitter API credentials
		consumer_key = "ThPs2SRcMr1apVG0CxpGKJFIx"
		consumer_secret = "GUsRVzhztAxjNu2T9MNrr4tOPPCxM9r6zu1LGR1JHkBTMrhcFV"
		access_key = "881327352-q78TpFwIkTmCwf4GTeDkQ98FTQcTtnYK8scYaJc8"
		access_secret = "SlvJOyjlpRfkIpe9qKEBcJdwudoVRjDENfHnj7T5Ufkeh"
		#########################################################
		twitter_input = self.twitter_hand_input.get()

		correct_input = True

		if twitter_input == "":
			correct_input = False

		correct_input = validate_twitter(twitter_input)

		if correct_input == False:
			self.twitter_hand_error['bg'] = "red"
			self.twitter_hand_error['text'] = "Enter a valid twitter handle!"
		else:
			self.twitter_hand_error['bg'] = "#e6e6e6"
			self.twitter_hand_error['text'] = ""
			# if twitter_input[0] != "@":
			# 	twitter_input = "@" + twitter_input
			count += 1
		#########################################################
		num_input = self.num_tweets_input.get()
		correct_input = validate_number(num_input)

		if correct_input == False:
			self.num_tweets_error['bg'] = "red"
			self.num_tweets_error['text'] = "Enter a valid number between 1 and 2500!"
		else:
			self.num_tweets_error['bg'] = "#e6e6e6"
			self.num_tweets_error['text'] = ""
			count += 1

		if count == 3:
			list_tweets = get_n_tweets(twitter_input, num_input)
			cleaned_tweets = clean_tweets(list_tweets)
			file_name = write_list_to_file(file_input, cleaned_tweets, twitter_input)
			self.file_name = file_name
			self.twitter_handle = twitter_input
			self.num_tweets = num_input
			self.get_tweets_button['state'] = 'disabled'
			self.train_program_button['state'] = 'normal'

	def train_program(self):
		count = 0
		#########################################################
		# subprocess.call(["g++", "HashTable.cpp", "ProductionWordGraphClass.cpp", "MainDriver.cpp", "TextTools.cpp", "FileToString.cpp", "AuthorStruct.cpp", "-std=c++11", "-o" , "Main"])
		file_input = self.file_dest_input.get()
		if file_input == "" or os.path.exists(file_input) == False:
			self.file_dest_error['bg'] = "red"
			self.file_dest_error['text'] = "Enter a valid file destination"
		else:
			self.file_dest_error['bg'] = "#e6e6e6"
			self.file_dest_error['text'] = ""
			count += 1
		#########################################################
		#Twitter API credentials
		consumer_key = "ThPs2SRcMr1apVG0CxpGKJFIx"
		consumer_secret = "GUsRVzhztAxjNu2T9MNrr4tOPPCxM9r6zu1LGR1JHkBTMrhcFV"
		access_key = "881327352-q78TpFwIkTmCwf4GTeDkQ98FTQcTtnYK8scYaJc8"
		access_secret = "SlvJOyjlpRfkIpe9qKEBcJdwudoVRjDENfHnj7T5Ufkeh"
		#########################################################
		twitter_input = self.twitter_hand_input.get()

		correct_input = True

		if twitter_input == "":
			correct_input = False

		correct_input = validate_twitter(twitter_input)

		if correct_input == False:
			self.twitter_hand_error['bg'] = "red"
			self.twitter_hand_error['text'] = "Enter a valid twitter handle!"
		else:
			self.twitter_hand_error['bg'] = "#e6e6e6"
			self.twitter_hand_error['text'] = ""
			# if twitter_input[0] != "@":
			# 	twitter_input = "@" + twitter_input
			count += 1
		#########################################################
		num_input = self.num_tweets_input.get()
		correct_input = validate_number(num_input)

		if correct_input == False:
			self.num_tweets_error['bg'] = "red"
			self.num_tweets_error['text'] = "Enter a valid number between 1 and 2500"
		else:
			self.num_tweets_error['bg'] = "#e6e6e6"
			self.num_tweets_error['text'] = ""
			count += 1
		#########################################################
		if count == 3:
			args = ['g++', 'HashTable.cpp', 'ProductionWordGraphClass.cpp', 'MainDriver.cpp', 'TextTools.cpp', 'FileToString.cpp', 'AuthorStruct.cpp', '-std=c++11', '-o', 'Main']
			p1 = subprocess.Popen(args, stdout=subprocess.PIPE)
			self.train_program_button['state'] = 'disabled'
			self.generate_tweet_button['state'] = 'normal'

	def generate_tweet(self):
		file_name = str(self.file_name)
		executable = ['./Main', file_name, '2']
		p = subprocess.Popen(executable, stdout=subprocess.PIPE, stdin=subprocess.PIPE)
		self.generated_tweet_text['text'] = str(p.stdout.read())
		self.generated_tweet_text['width'] = 500

		# if 0 == os.system(executable):
		# 	self.generate_tweet['state'] = 'disabled'
		# 	self.generate_tweet['state'] = 'normal'
		# else:
		#
		#     print('bad code from ./Main')
		# 	# os.system()


#########################################################
#########################################################
#########################################################

def clean_tweets(list_tweets):
	copy = list_tweets[:]
	return_list = list()

	i = 0
	for each_tweet in copy:

		# done
		lowered = each_tweet.lower() # works

		# done
		fixed = unescape(lowered) # works # important for 2270

		# done
		fixed2 = re.sub("[;\"'()]","", fixed) # this works...

		final = tokenize_text(fixed2)

		return_list.append(final)

		i += 1

	return return_list

#########################################################
#########################################################
#########################################################

def tokenize_text(str1):
	copy = str1
	punc = ",.;-"
	# fixes i -> I
	fixed_i = re.sub(r'(\si\s)', r' I ', copy) # fixes I

	fixed_punc1 = re.sub(r'([$.,!?-])', r' \1', fixed_i) # gives punc at end of words one space
	fixed_punc2 = re.sub(r'([$.,!?-])', r'\1 ', fixed_punc1) # gives punc at start of words one space

	# handles links
	fixed_links = fix_links(fixed_punc2) # works!

	# handles titles
	fixed_titles = fix_titles(fixed_links) # works!

	# handles contractions
	fixed_contractions = fix_contractions(fixed_titles)

	# handles acroynyms
	fixed_acronyms = fix_acroynyms(fixed_contractions)

	# handles spaces
	fixed_spaces = re.sub(r'(\s{2,})', ' ', fixed_acronyms) # works!

	fixed_periods = fix_multi_periods(fixed_spaces)

	return fixed_periods

#########################################################
#########################################################
#########################################################

def fix_links(str1):
	copy = str1

	# handles links
	copy = re.sub(r'https://t\s\.\s',"https://t.", copy) # fixes https://t. links
	copy = re.sub(r'\w\s\.\scom', '.com', copy) # fixes .com links

	return copy

#########################################################
#########################################################
#########################################################

def fix_contractions(str1):
	copy = str1

	# handles contractions
	copy = re.sub(r'ldnt', 'ldn\'t', copy) # ldnt
	copy = re.sub(r'cant', 'can\'t', copy) # cant
	copy = re.sub(r'dont', 'don\'t', copy) # dont
	copy = re.sub(r'wont', 'won\'t', copy) # wont
	copy = re.sub(r'eyre', 'ey\'re', copy) # theyre

	return copy

#########################################################
#########################################################
#########################################################

def fix_titles(str1):
	# titles = ["dr", "mr", "mrs", 'ms']
	copy = str1

	# handles titles
	copy = re.sub(r'(dr\s\.)', r'dr.', copy) # fixes dr.
	copy = re.sub(r'(mr\s\.)', r'mr.', copy) # fixes mr.
	copy = re.sub(r'(mrs\s\.)', r'mrs.', copy) # fixes mrs.
	copy = re.sub(r'(ms\s\.)', r'ms.', copy) # fixes ms.

	return copy

#########################################################
#########################################################
#########################################################

def fix_multi_periods(str1):
	copy = str1

	# DOES NOT WORK CURRENTLY...
	copy = re.sub(r'(\.\s\.\s\.\s\.\s\.\s\.)', r'....', copy) # fixes . . . . . . -> ......
	copy = re.sub(r'(\.\s\.\s\.\s\.\s\.)', r'....', copy) # fixes . . . . . -> .....
	copy = re.sub(r'(\.\s\.\s\.\s\.)', r'....', copy) # fixes . . . . -> ....
	copy = re.sub(r'(\.\s\.\s\.)', r'...', copy) # fixes . . . -> ...
	copy = re.sub(r'(\.\s\.)', r'..', copy) # fixes . . -> ..

	return copy

#########################################################
#########################################################
#########################################################

def fix_acroynyms(str1):
	# acronyms = ['u . k .', 'u . s .', 'u . s . a .',]
	copy = str1

	# handles acronyms
	copy = re.sub(r'u\s\.\ss\s\.\sa\s\.', r'U.S.A.', copy) # fixes u.s.a.
	copy = re.sub(r'u\s\.\ss\s\.', r'U.S.', copy) # fixes u.s.
	copy = re.sub(r'u\s\.\sk\s\.', r'U.K.', copy) # fixes u.k.
	copy = re.sub(r'd\s\.\sc\s\.', r'U.K.', copy) # fixes d.c.


	return copy

#########################################################
#########################################################
#########################################################

def unescape(str1):
	s = str1.replace("&amp;", "&")
	s = s.replace("&amp", "&")
	return s

#########################################################
#########################################################
#########################################################

def validate_twitter(twitter_input):
	#Twitter API credentials
	consumer_key = "ThPs2SRcMr1apVG0CxpGKJFIx"
	consumer_secret = "GUsRVzhztAxjNu2T9MNrr4tOPPCxM9r6zu1LGR1JHkBTMrhcFV"
	access_key = "881327352-q78TpFwIkTmCwf4GTeDkQ98FTQcTtnYK8scYaJc8"
	access_secret = "SlvJOyjlpRfkIpe9qKEBcJdwudoVRjDENfHnj7T5Ufkeh"
	#########################################################
	#authorize twitter, initialize tweepy
	auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
	auth.set_access_token(access_key, access_secret)
	api = tweepy.API(auth)
	#########################################################
	correct_input = True

	if twitter_input == "":
		correct_input = False

	else:
		try:
			for tweets in tweepy.Cursor(api.user_timeline, screen_name=twitter_input, count=1).items(1):
				id = tweets.user.id

		except tweepy.error.TweepError:
			correct_input = False

	return correct_input

#########################################################
#########################################################
#########################################################

def validate_number(num_input):
	try:
		num = int(num_input)
	except ValueError:
		return False

	if num_input == "" or num < 1 or num > 2500:
		return False
	else:
		return True

#########################################################
#########################################################
#########################################################

def get_n_tweets(screen_name, n):
	#########################################################
	#Twitter API credentials
	consumer_key = "ThPs2SRcMr1apVG0CxpGKJFIx"
	consumer_secret = "GUsRVzhztAxjNu2T9MNrr4tOPPCxM9r6zu1LGR1JHkBTMrhcFV"
	access_key = "881327352-q78TpFwIkTmCwf4GTeDkQ98FTQcTtnYK8scYaJc8"
	access_secret = "SlvJOyjlpRfkIpe9qKEBcJdwudoVRjDENfHnj7T5Ufkeh"
	#########################################################

	#########################################################
	#authorize twitter, initialize tweepy
	auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
	auth.set_access_token(access_key, access_secret)
	api = tweepy.API(auth)
	#########################################################

	fixed_tweets1 = list()

	try:
		for tweet in tweepy.Cursor(api.user_timeline, screen_name=screen_name, tweet_mode='extended', include_rts=False, count=n).items(n):
			fixed_tweet = str(tweet.full_text.encode('ascii',errors='ignore'))
			fixed_tweets1.append(fixed_tweet)

	except:
		print("Oops, could not get any tweets, try the program again")
		return 0

	return fixed_tweets1

#########################################################
#########################################################
#########################################################

def write_list_to_file(path_name, list1, username):
	if list1 != None:
		fixed_username = username[:]

		file_name = path_name + '@' + fixed_username + ".txt"

		file1 = open(file_name, "w")

		file1.write(" * ")

		for each in list1:
			# each = tokenize_text(each)
			file1.write(each.encode("utf-8"))
			file1.write(" * ")

		return file_name

#########################################################
#########################################################
#########################################################


if __name__ == '__main__':

    # subprocess.call(['/usr/bin/osascript', '-e', 'tell app "Finder" to set frontmost of process "Python" to true'])

    root = tk.Tk()

    app = App(root)

    app.mainloop()
# root.destroy() # optional; see description below
