#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to encrypt a message using the Rail Fence Cipher
string encryptRailFence(const string &message, int rails)
{
    vector<string> fence(rails, "");
    int currentRail = 0;
    bool goingDown = false;

    for (char c : message)
    {
        fence[currentRail] += c;

        if (currentRail == 0 || currentRail == rails - 1)
        {
            goingDown = !goingDown;
        }

        currentRail += goingDown ? 1 : -1;
    }

    string encryptedMessage = "";
    for (const string &rail : fence)
    {
        encryptedMessage += rail;
    }

    return encryptedMessage;
}

// Function to decrypt a message encrypted with the Rail Fence Cipher
string decryptRailFence(const string &message, int rails)
{
    vector<string> fence(rails, "");
    vector<int> railSizes(rails, 0);
    int currentRail = 0;
    bool goingDown = false;

    for (int i = 0; i < message.length(); i++)
    {
        railSizes[currentRail]++;

        if (currentRail == 0 || currentRail == rails - 1)
        {
            goingDown = !goingDown;
        }

        currentRail += goingDown ? 1 : -1;
    }

    int messageIndex = 0;
    for (int rail = 0; rail < rails; rail++)
    {
        fence[rail] = message.substr(messageIndex, railSizes[rail]);
        messageIndex += railSizes[rail];
    }

    string decryptedMessage = "";
    currentRail = 0;
    goingDown = false;

    for (int i = 0; i < message.length(); i++)
    {
        decryptedMessage += fence[currentRail][0];
        fence[currentRail].erase(0, 1);

        if (currentRail == 0 || currentRail == rails - 1)
        {
            goingDown = !goingDown;
        }

        currentRail += goingDown ? 1 : -1;
    }

    return decryptedMessage;
}

int main()
{
    string message;
    int rails;

    cout << "Enter a message: ";
    getline(cin, message);

    cout << "Enter the number of rails: ";
    cin >> rails;

    string encryptedMessage = encryptRailFence(message, rails);
    string decryptedMessage = decryptRailFence(encryptedMessage, rails);

    cout << "Encrypted message: " << encryptedMessage << endl;
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}
