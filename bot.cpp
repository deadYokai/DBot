#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <curl/curl.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string getJoke(){
	string readBuffer;
	CURL *curl;
        curl = curl_easy_init();
        if(curl) {
                curl_easy_setopt(curl, CURLOPT_URL, "https://vilafox.xyz/engine/ds/api?act=getJoke");
    		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return readBuffer;
}

void netClient(string hostName, uint16_t port)
{
    bool connected = false;
    int sock;

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1)
        printf("SOCKERR\n");

    fcntl(sock, F_SETFL, O_NONBLOCK);


    sockaddr_in addr;
    // Memory::Clear(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    uint32_t ipAddr = 0;

    ipAddr = inet_addr(hostName.c_str());

    addr.sin_addr.s_addr = ipAddr;
    cout << "Connecting to " << hostName.c_str() << " => " << ipAddr;
    printf("Connecting to '%s' => '%d.%d.%d.%d', port %d\n",
        hostName.c_str(),
        ipAddr & 0xFF,
        (ipAddr >> 8) & 0xFF,
        (ipAddr >> 16) & 0xFF,
        (ipAddr >> 24) & 0xFF,
        port);

    const int connectRes = connect(sock, (sockaddr*)&addr, sizeof(addr));
    if (-1 == connectRes) {
        if (((errno == EINPROGRESS) || (errno == EWOULDBLOCK) || (errno == EISCONN))) {
            connected = true;
        }
    }
    if (!connected)
        printf("Failed to connect to '%s:%d'\n", hostName.c_str(), port);

    fd_set fdr, fdw;
    FD_ZERO(&fdr);
    FD_ZERO(&fdw);
    FD_SET(sock, &fdr);
    FD_SET(sock, &fdw);

    // for windows, it is necessary to provide an empty timeout
    // structure, in order for select() to not block
    struct timeval tv = { };
    const int selectRes = select(int(sock+1), &fdr, &fdw, 0, &tv);
    if (selectRes == -1) {
        printf("select() failed.\n");
    }
    else if (selectRes > 0) {
        printf("Try\n");
        if (FD_ISSET(sock, &fdr)) {
            printf("Should Recv OK!\n");
        }
        if (FD_ISSET(sock, &fdw)) {
            printf("Should Send OK!\n");
        }
    }
    printf("selectedRes: %d\n", selectRes);
}

void sendJoke(string token){
        CURL *curl;
        curl = curl_easy_init();
        string post = "content=" + getJoke();
        cout << "POST: " << post << endl;
        struct curl_slist *headers = NULL;
        if(curl) {
                headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (compatible; Discordbot/2.0; +https://discordapp.com)");
                headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
                string a = "Authorization: Bot " + token;
                headers = curl_slist_append(headers, a.c_str());
                curl_easy_setopt(curl, CURLOPT_URL, "https://discordapp.com/api/gateway");
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_POST, 1);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());
                curl_easy_perform(curl);
               curl_easy_cleanup(curl);
               cout << endl;
        }
	netClient("gateway.discord.gg", 80);
}


void launch(){
	cout << "Bot token checking...\n";
	string token;
  	ifstream myfile ("bot_token");
	if (myfile.is_open())
	{
		cout << "Authorize as ";
		getline (myfile,token);
		cout << token;
		cout << "\n\n";
		myfile.close();
	}else{  
		cout << "Bot Token not found.\n";
		cout << "Enter Bot Token: ";
		getline (cin, token);
		ofstream myfile;
		myfile.open ("bot_token");
		myfile << token;
		myfile.close();
		cout << "New token:"<< token <<"\n\n";
    	}
	CURL *curl;
	curl = curl_easy_init();
	string post = "content=" + getJoke();
	cout << "POST: " << post << endl;
	struct curl_slist *headers = NULL;
	if(curl) {
		headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (compatible; Discordbot/2.0; +https://discordapp.com)");
		headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
		string a = "Authorization: Bot " + token;
		headers = curl_slist_append(headers, a.c_str());
		curl_easy_setopt(curl, CURLOPT_URL, "https://discordapp.com/api/gateway/bot");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		cout << endl;
	}

    // TODO
}

int main(int argc, char **argv)
{
  cout << "Hello my friend! \n\n";
  cout << "DBot by VFox Team (http://vfoxteam.vilafox.xyz/) \n";
  cout << "Discord: https://discord.gg/sQxPPQD \n\n";

  if( (argc > 1) ){
  	map <string, int> mapping;

	mapping["-h"]  = 1;
	mapping["--help"]  = 1;
	mapping["-d"]    = 2;
	mapping["--delete_token"] = 2;
	switch(mapping[string(argv[1])]){

		case 1:
	  		cout << "Usage:\n";
	  		cout << "without arguments 	-- start bot\n";
	  		cout << "-h or --help 		-- display this text\n";
	  		cout << "-d or --delete_token 	-- delete bot_token\n";
	  		break;

		case 2:
			cout << "Deleting token... ";
      		remove("bot_token");
      		cout << "Done.\n";
		break;

		default:
			cout << "Use a --help or -h argument to see a usage\n";
			break;

	}
  	
  }else{
  	launch();
  }
  return 0;
}
