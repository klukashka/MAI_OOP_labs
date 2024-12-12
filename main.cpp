#include "./include/NPCFactory.hpp"
#include "./include/NPC.hpp"
// #include "./include/Arena.hpp"
// #include "./include/NPCFactory.hpp"
// #include "./include/Observers.hpp"
// #include "./include/NPC.hpp"
// #include "./include/Dragon.hpp"
// #include "./include/Druid.hpp"
// #include "./include/Elf.hpp"
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <random>
#include <atomic>
#include <chrono>
#include <vector>
#include <mutex>

std::vector<std::shared_ptr<NPC>> npcs;
std::shared_mutex npc_mutex;
std::mutex cout_mutex;
std::atomic<bool> game_running = true;

constexpr int MAP_WIDTH = 500;
constexpr int MAP_HEIGHT = 500;
constexpr int GAME_DURATION = 30;

int roll_dice() {
    static thread_local std::mt19937 rng(std::random_device{}());
    return std::uniform_int_distribution<int>(1, 6)(rng);
}

int random_range(int min, int max) {
    static thread_local std::mt19937 rng(std::random_device{}());
    return std::uniform_int_distribution<int>(min, max)(rng);
}

void move_npcs() {
    while (game_running) {
        {
            std::unique_lock lock(npc_mutex);
            for (auto& npc : npcs) {
                if (npc->serialize().find("dead") == std::string::npos) {
                    int dx = random_range(-npc->move_dist, npc->move_dist);
                    int dy = random_range(-npc->move_dist, npc->move_dist);

                    npc->x = std::max(0, std::min(MAP_WIDTH - 1, npc->x + dx));
                    npc->y = std::max(0, std::min(MAP_HEIGHT - 1, npc->y + dy));
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void combat_npcs() {
    while (game_running) {
        {
            std::unique_lock lock(npc_mutex);
            for (size_t i = 0; i < npcs.size(); ++i) {
                if (npcs[i]->serialize().find("dead") != std::string::npos) continue;

                for (size_t j = i + 1; j < npcs.size(); ++j) {
                    if (npcs[j]->serialize().find("dead") != std::string::npos) continue;

                    double distance = npcs[i]->distance_to(npcs[j].get());
                    if (distance <= npcs[i]->kill_dist || distance <= npcs[j]->kill_dist) {
                        int attack = roll_dice();
                        int defense = roll_dice();

                        if (attack > defense) {
                            npcs[j]->type += "_dead";
                            std::lock_guard<std::mutex> cout_lock(cout_mutex);
                            std::cout << npcs[i]->get_name() << " убил " << npcs[j]->get_name() << "\n";
                        } else if (defense > attack) {
                            npcs[i]->type += "_dead";
                            std::lock_guard<std::mutex> cout_lock(cout_mutex);
                            std::cout << npcs[j]->get_name() << " убил " << npcs[i]->get_name() << "\n";
                        }
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void print_map() {
    while (game_running) {
        std::vector<std::vector<char>> map(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, '.'));
        {
            std::shared_lock lock(npc_mutex);
            for (const auto& npc : npcs) {
                if (npc->serialize().find("dead") == std::string::npos) {
                    map[npc->y][npc->x] = npc->get_name()[0];
                }
            }
        }
        {
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            std::cout << "\033[2J\033[H";  // clear and move home
            for (const auto& row : map) {
                for (char cell : row) {
                    std::cout << cell;
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    for (int i = 0; i < 50; ++i) {
        int x = random_range(0, MAP_WIDTH - 1);
        int y = random_range(0, MAP_HEIGHT - 1);


        std::string type;
        if (i % 3 == 0) type = "Dragon";
        else if (i % 3 == 1) type = "Druid";
        else type = "Elf";

        npcs.push_back(NPCFactory::createNPC(type, type + std::to_string(i), x, y));
    }

    std::thread move_thread(move_npcs);
    std::thread combat_thread(combat_npcs);
    std::thread print_thread(print_map);

    std::this_thread::sleep_for(std::chrono::seconds(GAME_DURATION));
    game_running = false;

    move_thread.join();
    combat_thread.join();
    print_thread.join();

    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    std::cout << "Игра окончена. Выжившие NPC:\n";
    {
        std::shared_lock lock(npc_mutex);
        for (const auto& npc : npcs) {
            if (npc->serialize().find("dead") == std::string::npos) {
                std::cout << npc->get_name() << " (" << npc->x << ", " << npc->y << ")\n";
            }
        }
    }
    return 0;
}