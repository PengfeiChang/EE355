
#include "misc.h"

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}

string codeName(string str1, string str2){

    string str;
    //Remove the whitespace for str1
    //iterate through the string to store only non-space character
    int length = 0;
    for(int i=0; i< str1.length(); i++)
    {
        if(str1[i] != ' ')
        {
            str1[length++] = str1[i];
        }
    }

    //decrease the length of the string 
    str1 = str1.substr(0,length);

    //Remove whitespace for str2 as well
    //iterate through the string to store only non-space character
    length = 0;
    for(int i=0; i< str2.length(); i++)
    {
        if(str2[i] != ' ')
        {
            str2[length++] = str2[i];
        }
    }

    //decrease the length of the string
    str2 = str2.substr(0,length);

    //convert str1 to lower case with help of function tolower()
    int i=0;
    while(str1[i])
    {
        str1[i] = tolower(str1[i]);
        i++;
    }

    //convert str2 to lower case with help of function tolower()
    int j=0;
    while(str2[j])
    {
        str2[j] = tolower(str2[j]);
        j++;
    }

    str = str1 + str2;

    return str;

}