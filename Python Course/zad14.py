import requests
from bs4 import BeautifulSoup
import spacy
from textblob import TextBlob
import spacy
import plotly.graph_objects as go


nlp = spacy.load("en_core_web_sm")
BASE_URL = 'https://edition.cnn.com'

def analyze_webpage_sentiment(url):
    response = requests.get(url)
    soup = BeautifulSoup(response.content, 'html.parser')
    text = ' '.join(map(lambda p: p.text, soup.find_all('p')))
    doc = nlp(text)
    processed_text = ' '.join([token.lemma_ for token in doc if not token.is_stop])
    sentiment = TextBlob(processed_text).sentiment
    
    return sentiment

def get_articles(url):
    link_set = set()
    page = requests.get(url)
    soup = BeautifulSoup(page.content, 'html.parser')
    all_links = soup.find_all('a', href=True)
    for link in all_links:
        if link['href'].startswith('/2024'):
            link_set.add(link['href'])
    return list(link_set)

def get_article_title(url):
    response = requests.get(url)
    soup = BeautifulSoup(response.content, 'html.parser')
    return soup.title.string

def get_average_sentiment(url, articles_per_topic):
    polarity_sum = 0
    subjectivity_sum = 0
    article_links = get_articles(url)
    for i in range(articles_per_topic):
        link = article_links[i]
        polarity_sum += analyze_webpage_sentiment(BASE_URL + link).polarity
        subjectivity_sum += analyze_webpage_sentiment(BASE_URL + link).subjectivity
    return {
        'polarity': polarity_sum / articles_per_topic,
        'subjectivity': subjectivity_sum / articles_per_topic
    }

topics = ['world', 'politics', 'business', 'health', 'entertainment', 'style', 'travel', 'sports']
average_polarities = {topic: get_average_sentiment(BASE_URL + '/' + topic, 2) for topic in topics}

fig = go.Figure(data=[
    go.Bar(name='Polarity', x=topics, y=[average_polarities[topic]['polarity'] for topic in topics]),
    go.Bar(name='Subjectivity', x=topics, y=[average_polarities[topic]['subjectivity'] for topic in topics])
])

fig.show()
print(average_polarities)

