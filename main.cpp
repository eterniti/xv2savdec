#include "DBXV2/Xv2SavFile.h"
#include "debug.h"

bool toggle_encryption(const std::string &file)
{
	bool encrypt;
	std::string output;
	
	if (Utils::EndsWith(file, ".sav", false))
	{
		encrypt = false;
		output = file + ".dec";
	}
	else if (Utils::EndsWith(file, ".sav.dec", false))
	{
		encrypt = true;
		output = file.substr(0, file.length()-4);
	}
	else
	{
		DPRINTF("Extension must be .sav or .sav.dec.\n");
		return false;
	}
	
	Xv2SavFile sav;
	
	if (!sav.LoadFromFile(file))
	{
		DPRINTF("Failed to load file.\n");
		return false;
	}
	
	sav.SetEncrypted(encrypt);
	
	if (!sav.SaveToFile(output))
	{
		DPRINTF("Failed saving file.\n");
		return false;
	}
	
	return true;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		DPRINTF("Usage: %s file.sav (or file.sav.dec)\n", argv[0]);
		return -1;
	}
	
	if (!toggle_encryption(argv[1]))
	{
		UPRINTF("Press enter to exit.");
        getchar();
	}
	
	return 0;
}
