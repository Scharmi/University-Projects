from bs4 import BeautifulSoup
import requests
import random
import pandas as pd
def get_hour(url):
    page = requests.get(url)
    soup = BeautifulSoup(page.content, 'html.parser')
    if(len(soup.find_all("div", class_="kanal-data")) == 0):
        return ""
    hour_div = soup.find_all("div", class_="kanal-data")[0]
    hour = hour_div.text
    hour = hour.replace("\n", "")
    hour = " ".join(hour.split())
    return hour
def get_events(url):
    list = []
    page = requests.get(url)
    soup = BeautifulSoup(page.content, 'html.parser')
    if len(soup.find_all("div", class_="kolumny clearfix")) == 0:
        print("Error: " + page)
        return list
    events = soup.find_all("div", class_="kolumny clearfix")[0].find_all("a")
    events = [event for event in events if event["href"].startswith("/aktualnosci/wydarzenia")]
    for event in events:
        new_val = {}
        new_val["url"] = "https://www.mimuw.edu.pl/" + event["href"]
        new_val["date"] = get_hour(new_val["url"])
        new_val["title"] = event.text
        list.append(new_val)
    return list
list = get_events("https://www.mimuw.edu.pl/aktualnosci/wydarzenia")
for i in range(1, 5):
    print(i)
    new_list = get_events("https://www.mimuw.edu.pl/aktualnosci/wydarzenia?page=" + str(i))
    if len(new_list) == 0:
        print("Error: " + str(i))
    list = list + new_list
df = pd.DataFrame(list)
df.to_csv('events.csv', index=True)
for i in range(0,5):
    print(list[random.randint(0, len(list))])