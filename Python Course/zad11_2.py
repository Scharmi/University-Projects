import requests
from bs4 import BeautifulSoup
import spacy
from textblob import TextBlob
import spacy

nlp = spacy.load("en_core_web_sm")

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
    return link_set

def get_article_title(url):
    response = requests.get(url)
    soup = BeautifulSoup(response.content, 'html.parser')
    return soup.title.string

article_links = get_articles('https://edition.cnn.com/world')
for link in article_links:
    print(get_article_title('https://edition.cnn.com' + link))
    print(analyze_webpage_sentiment('https://edition.cnn.com' + link))
    print()
