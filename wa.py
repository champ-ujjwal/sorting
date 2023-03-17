import pyautogui
import time
time.sleep(2)
count=0
while count<=100:
    pyautogui.typewrite("u r spending ur money in wrong things")
    pyautogui.press("enter")
    count=count+1