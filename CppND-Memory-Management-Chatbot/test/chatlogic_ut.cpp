#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/chatlogic.h"
#include "../src/graphnode.h"

using namespace testing;

TEST(ChatLogicTest, Test_LoadAnswerGraphFromFile) {
    ChatLogic chatLogic{};

    chatLogic.LoadAnswerGraphFromFile("../src/answergraph.txt");

    // Check size of initialized node vector is 8, based on the number of answer in src/answergraph.txt
    EXPECT_EQ(chatLogic.Nodes().size(), 8);

    // Check current chatbot is set at root node
    ASSERT_NE(chatLogic.Nodes().at(0)->GetChatBot()->GetChatLogicHandle(), nullptr);
    EXPECT_EQ(chatLogic.Nodes().at(0)->GetChatBot()->GetChatLogicHandle(), &chatLogic);
    ASSERT_NE(chatLogic.Nodes().at(0)->GetChatBot()->CurrentNode(), nullptr);
    ASSERT_NE(chatLogic.Nodes().at(0)->GetChatBot()->RootNode(), nullptr);
    EXPECT_EQ(chatLogic.Nodes().at(0)->GetChatBot()->CurrentNode()->GetID(), chatLogic.Nodes().at(0)->GetChatBot()->RootNode()->GetID());

    // Chatbot at other nodes have root node and chatlogic handle member is nullptr
    for (int i = 1; i < 8; i++) {
        ASSERT_EQ(chatLogic.Nodes().at(i)->GetChatBot()->RootNode(), nullptr);
        ASSERT_EQ(chatLogic.Nodes().at(i)->GetChatBot()->GetChatLogicHandle(), nullptr);
    }
}