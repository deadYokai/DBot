# DBot
Discord Bot on C++

Requires: curl, openssl, g++

## Compiling

```bash
g++ -g -Wall -o <your_output_name> bot.cpp -lcurl
```

## Installing packages

G++:
```bash
apt-get install build-essential
apt-get install g++
```

cURL:
```bash
apt-get install libcurl-dev
```
OR
```bash
apt-get install libcurl4-openssl-dev 
```

OpenSSL:
```bash
apt-get install openssl
apt-get install libssl-dev
```

## Warning!

Change variables

```c+
curl_easy_setopt(curl, CURLOPT_URL, "https://discordapp.com/api/channels/<here>/messages");  <-- Here change to your channel id
```
