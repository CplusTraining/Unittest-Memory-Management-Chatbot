#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/chatlogic.h"
#include "../src/graphnode.h"
#include <iostream>
#include <vector>

using namespace testing;
using namespace std;

#define TEST_FAILED_MSG(id, testCaseNo) "failed at " << id << " of "  << testCaseNo << "\n"

string genRandomStr(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string tmp;
    tmp.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp;
}

TEST(ChatBotTest, Test_ReceiveMessageFromUser) {
    auto checkChatBotOfNodes = [](vector<string> msgs, int testCaseNo){
        int id = stoi(msgs.back());
        msgs.pop_back();

        ChatLogic chatLogic{};
        chatLogic.LoadAnswerGraphFromFile("../src/answergraph.txt");

        // Move the chat bot according to the list of input message
        for (auto &msg:msgs) {
            for (auto &node:chatLogic.Nodes()) {
                if (node->GetChatBot()->GetChatLogicHandle() != nullptr) {
                    node->GetChatBot()->ReceiveMessageFromUser(msg);
                    break;
                }
            }
        }

        // Check the last position of chat bot is the same as the expected node id
        for (int i = 0; i < chatLogic.Nodes().size(); i++) {
            ChatBot *chatBot = chatLogic.Nodes().at(i)->GetChatBot();
            if (i == id) {
                ASSERT_NE(chatBot->CurrentNode(), nullptr)           << TEST_FAILED_MSG(id, testCaseNo);
                ASSERT_EQ(chatBot->CurrentNode()->GetID(), id)       << TEST_FAILED_MSG(id, testCaseNo);
                ASSERT_NE(chatBot->GetChatLogicHandle(), nullptr)    << TEST_FAILED_MSG(id, testCaseNo);
                ASSERT_NE(chatBot->RootNode(), nullptr)              << TEST_FAILED_MSG(id, testCaseNo);
                ASSERT_EQ(chatBot->GetChatLogicHandle(), &chatLogic) << TEST_FAILED_MSG(id, testCaseNo);
                ASSERT_NE(chatBot->GetImageHandle(), nullptr)        << TEST_FAILED_MSG(id, testCaseNo);
            } else {
                ASSERT_EQ(chatBot->GetChatLogicHandle(), nullptr)    << TEST_FAILED_MSG(id, testCaseNo);
                ASSERT_EQ(chatBot->GetImageHandle(), nullptr)        << TEST_FAILED_MSG(id, testCaseNo);
            }
        }
    };

    string emptyStr = "";
    string randomStr = genRandomStr(20); // Randome 20 lenght string

    // List of key of each edge ID based on answergraph.txt
    vector<string> keyID1 = {"pointer", "smart pointer"};
    vector<string> keyID2 = {"memory model", "heap", "stack"};
    vector<string> keyID3 = {"unique pointer", "shared pointer", "weak pointer"};
    vector<string> keyID4 = {"NULL", "null pointer", "nullptr"};
    vector<string> keyID5 = {"stack", "stack memory", "local variable storage"};
    vector<string> keyID6 = {"heap", "heap memory", "dynamic storage"};
    vector<string> keyID7 = {"static", "static memory", "global variable storage"};

    vector<string> expectedOutput = {"0", "1", "2", "3", "4", "5", "6", "7"};

    vector<vector<string>> testSets = {
        {keyID1[0],                       expectedOutput[1]},
        {keyID1[1],                       expectedOutput[1]},
        {randomStr,                       expectedOutput[1]},
        {emptyStr,                        expectedOutput[2]},
        {keyID2[0],                       expectedOutput[2]},
        {keyID2[1],                       expectedOutput[2]},
        {keyID2[2],                       expectedOutput[2]},
        {keyID1[0], keyID3[0],            expectedOutput[3]},
        {keyID1[0], keyID3[1],            expectedOutput[3]},
        {keyID1[0], keyID3[2],            expectedOutput[3]},
        {keyID1[0], keyID4[0],            expectedOutput[4]},
        {keyID1[0], keyID4[1],            expectedOutput[4]},
        {keyID1[0], keyID4[2],            expectedOutput[4]},
        {keyID2[0], keyID5[0],            expectedOutput[5]},
        {keyID2[0], keyID5[1],            expectedOutput[5]},
        {keyID2[0], keyID5[2],            expectedOutput[5]},
        {keyID2[0], keyID6[0],            expectedOutput[6]},
        {keyID2[0], keyID6[1],            expectedOutput[6]},
        {keyID2[0], keyID6[2],            expectedOutput[6]},
        {keyID2[0], randomStr,            expectedOutput[6]},
        {keyID2[1], randomStr,            expectedOutput[6]},
        {keyID2[2], randomStr,            expectedOutput[6]},
        {keyID2[0], emptyStr,             expectedOutput[6]},
        {keyID2[1], emptyStr,             expectedOutput[6]},
        {keyID2[2], emptyStr,             expectedOutput[6]},
        {keyID2[0], keyID7[0],            expectedOutput[7]},
        {keyID2[0], keyID7[1],            expectedOutput[7]},
        {keyID2[0], keyID7[2],            expectedOutput[7]},
        {keyID1[0], keyID3[0], emptyStr,  expectedOutput[0]},
        {keyID1[0], keyID3[0], randomStr, expectedOutput[0]},
        {keyID1[0], keyID4[0], emptyStr,  expectedOutput[0]},
        {keyID1[0], keyID4[0], randomStr, expectedOutput[0]},
        {keyID2[0], keyID5[0], emptyStr,  expectedOutput[0]},
        {keyID2[0], keyID5[0], randomStr, expectedOutput[0]},
        {keyID2[0], keyID6[0], emptyStr,  expectedOutput[0]},
        {keyID2[0], keyID6[0], randomStr, expectedOutput[0]},
        {keyID2[0], keyID7[0], emptyStr,  expectedOutput[0]},
        {keyID2[0], keyID7[0], randomStr, expectedOutput[0]},
    };

    int testSetCount = 0;
    for (auto &set:testSets) {
        checkChatBotOfNodes(set, testSetCount);
        testSetCount++;
    }
}