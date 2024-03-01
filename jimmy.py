import speech_recognition as sr
import pyttsx3
import pyaudio
import datetime
import wikipedia

engine = pyttsx3.init('sapi5')
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[0].id)

def speak(audio):
    engine.say(audio)
    engine.runAndWait()

def service():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        r.pause_threshold = 0.6
        audio = r.listen(source)

    try:
        print("Recognizing...")
        query = r.recognize_google(audio, language='en-in')
        print(f"User Said: {query}")
        return query

    except Exception as e:
        print("Error:", e)
        speak("Some Error Occurred. Sorry From Jimmy")
        speak("Can you please repeat it?")
        return " "

def showTime():
    now = datetime.datetime.now()
    hour = now.hour
    minute = now.minute
    second = now.second
    time_str = f"The current time is {hour}, {minute}, and {second} seconds"
    speak(time_str)
    return hour, minute, second

if __name__ == "__main__":
    speak("Hello, I am Jimmy")
    speak("How can I assist you?")
    while True:
        print("Listening...")
        query = service().lower()
        
        if "how are you".lower() in query.lower():
            speak("I am Fine What About you")
            
        if "tell me something about you".lower() in query.lower():
            speak("i am Jimmay 3.0,an AI Model develop by TechBoys.i am designed to engage in conversations,provide information and assist users")
            
        if "what's the time".lower() in query.lower():
            hour, minute, second = showTime()
            
        if "jimmy" in query:
            speak("Searching..")
            query = query.replace("wikipedia", "")
            results = wikipedia.summary(query)
            speak(results)

        

        
