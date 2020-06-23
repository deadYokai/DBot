#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <curl/curl.h>

using namespace std;

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
	CURLcode res;
	curl = curl_easy_init();
	struct curl_slist *headers = NULL;
	if(curl) {
		headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (compatible; Discordbot/2.0; +https://discordapp.com)");
		headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
		string a = "Authorization: Bot " + token;
		headers = curl_slist_append(headers, a.c_str());
		curl_easy_setopt(curl, CURLOPT_URL, "https://discordapp.com/api/channels/721018480761110618/messages");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "content=Если вы заблудились и очень устали - позовите кровососа\nУсталость как рукой снимет");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		cout << res << "\n";
                cout << "Headers:" << headers << "\n";

	}

    // TODO
}

int main(int argc, char **argv)
{
  cout << "Build 1804.14062020 \n\n";
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
