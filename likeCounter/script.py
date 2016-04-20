import urllib, json
url = "https://graph.facebook.com/gopeon/?fields=fan_count&access_token=260256070983293|2710385e8b869f36f79d3b0bc0d1df75"
response = urllib.urlopen(url)
data = json.loads(response.read())
print data['fan_count']