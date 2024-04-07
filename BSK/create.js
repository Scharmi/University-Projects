await fetch("https://web.kazet.cc:42448/create", {
    "credentials": "include",
    "headers": {
        "User-Agent": "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/119.0",
        "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
        "Accept-Language": "en-GB,en;q=0.5",
        "Content-Type": "application/x-www-form-urlencoded",
        "Upgrade-Insecure-Requests": "1",
        "Sec-Fetch-Dest": "document",
        "Sec-Fetch-Mode": "navigate",
        "Sec-Fetch-Site": "same-origin",
        "Sec-Fetch-User": "?1"
    },
    "referrer": "https://web.kazet.cc:42448/create",
    "body": "csrfmiddlewaretoken=euadqvSOoHu5JbuEJI6cPe7k43yM8hJNRzD5jNQP040q7TpXdPmchUX0j5yYos4e&recipient=admin&content=%3Cp%3EXD%3C%2Fp%3E&template=normal",
    "method": "POST",
    "mode": "cors"
});