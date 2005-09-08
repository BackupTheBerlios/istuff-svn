# Originally this script should clean all process related to this demo, but
# ps -a | grep EHtoApple | awk '{kill $1}'
# didn't work somehow.
# So this script just show the relevant processes to be killed
ps -a | grep EHtoApple 
ps -a | grep SpeechServer 
ps -a | grep Intermediary 
