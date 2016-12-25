from robot_modules import Listener, Responder, get_response

listener = Listener()
responder = Responder()

responder.default()

while True:

  phrase = listener.hear()
  
  if phrase:
    response = get_response(phrase)
    responder.show(response)

'''
say the following: 
1. hello 
2. hey
3. hi
4. up
5. name
6. do you do 
7. office #FIX THIS, NOT WORKING YET 
8. plans
9. tonight
10. advice
11. idea
12. help 
13. anything
'''
