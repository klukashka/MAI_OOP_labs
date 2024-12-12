#include <gtest/gtest.h>
#include "../include/NPCFactory.hpp"

TEST(NPCTest, CreateNPC) {
    auto npc = NPCFactory::createNPC("Dragon", "Dragon1", 100, 200);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->get_type(), "Dragon");
    EXPECT_EQ(npc->get_name(), "Dragon1");
    EXPECT_EQ(npc->x, 100);
    EXPECT_EQ(npc->y, 200);
}

TEST(NPCTest, DeserializeNPC) {
    std::string data = "Elf Elf1 300 400";
    auto npc = NPC::deserialize(data);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->get_type(), "Elf");
    EXPECT_EQ(npc->get_name(), "Elf1");
    EXPECT_EQ(npc->x, 300);
    EXPECT_EQ(npc->y, 400);
}

TEST(NPCTest, DeserializeInvalidNPC) {
    std::string data = "InvalidType Unknown 0 0";
    auto npc = NPC::deserialize(data);
    EXPECT_EQ(npc, nullptr);
}

TEST(NPCTest, DistanceToNPC) {
    auto npc1 = NPCFactory::createNPC("Druid", "Druid1", 100, 200);
    auto npc2 = NPCFactory::createNPC("Elf", "ELf1", 150, 250);

    double distance = npc1->distance_to(npc2.get());
    EXPECT_NEAR(distance, 70.7107, 0.0001);
}

TEST(NPCTest, SaveAndLoadNPCsFromFile) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(NPCFactory::createNPC("Dragon", "Dragon1", 100, 200));
    npcs.push_back(NPCFactory::createNPC("Elf", "ELf1", 150, 250));

    const std::string filename = "test_npcs.txt";
    save_npc_to_file(npcs, filename);

    std::vector<std::shared_ptr<NPC>> loadedNPCs = load_npc_from_file(filename);

    ASSERT_EQ(loadedNPCs.size(), 2);
    EXPECT_EQ(loadedNPCs[0]->get_type(), "Dragon");
    EXPECT_EQ(loadedNPCs[1]->get_type(), "Elf");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}