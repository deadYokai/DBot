#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

void launch(){
	cout << "Bot token checking...\n";
	string token;
	string line;
  	ifstream myfile ("bot_token");
	if (myfile.is_open())
	{
		cout << "Authorize as ";
	    while ( getline (myfile,line) )
	    {
	      cout << line << '\n';
	    }
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