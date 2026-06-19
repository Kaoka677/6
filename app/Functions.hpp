#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "Algorithms.hpp"
#include "AVL.hpp"
#include "BST.hpp"
#include "HashTable.hpp"
#include "LinkedList.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "Stack.hpp"

#include <iostream>
#include <string>

using namespace std;

struct Item
{
    string id;
    string name;
    string type;
    int attack;
    int defense;
    int value;
    int weight;
    int quantity;
    Item();
    Item(string i, string n, string t, int a, int d, int v, int w, int q = 1);
};

struct Player
{
    string name;
    int hp;
    int maxHp;
    int baseAttack;
    int baseDefense;
    int speed;
    int currentWeight;
    AVL<Item> inventory;
    Item *equippedWeapon;
    Item *equippedArmor;
    Player(string n);
};

struct Boss
{
    string id;
    string name;
    int hp;
    int attack;
    int defense;
    int speed;
    string dropItemId;
    Boss();
    Boss(string i, string n, int h, int a, int d, int s, string drop);
};

inline bool operator<(const Item &item1, const Item &item2) { return (item1.id < item2.id); }
inline bool operator>(const Item &item1, const Item &item2) { return (item1.id > item2.id); }
inline bool operator==(const Item &item1, const Item &item2) { return (item1.id == item2.id); }
inline bool operator<(const Boss &b1, const Boss &b2) { return (b1.id < b2.id); }
inline bool operator>(const Boss &b1, const Boss &b2) { return (b1.id > b2.id); }
inline bool operator==(const Boss &b1, const Boss &b2) { return (b1.id == b2.id); }

struct CompareWeight
{
    bool operator()(const Item &a, const Item &b) const { return a.weight > b.weight; }
};
struct CompareValue
{
    bool operator()(const Item &a, const Item &b) const { return a.value > b.value; }
};
struct CompareName
{
    bool operator()(const Item &a, const Item &b) const { return a.name < b.name; }
};

string HashPassword(const string &pass);
void LoadItemsFromFile(const string &filename, HashTable<string, Item> &itemDB);
void LoadBossesFromFile(const string &filename, HashTable<string, Boss> &bossDB);
void LoadAccounts(const string &filename, HashTable<string, string> &accDB);
void SaveAccount(const string &filename, const string &user, const string &pass);
int TotalAttack(const Player &player);
int TotalDefense(const Player &player);
int TotalWeight(const Player &player);
void UnequipWeapon(Player &player);
void UnequipArmor(Player &player);
void EquipItem(Player &player, const string &itemId);
void DropItem(Player &player, const string &itemId, int amount);
void Combat(Player &player, Boss boss, const HashTable<string, Item> &itemDB);
void LoadRecipesFromFile(const string &filename, HashTable<string, string> &recipeDB);
void CraftItem(Player &player, const string &id1, const string &id2, const HashTable<string, string> &recipeDB, const HashTable<string, Item> &itemDB);
void SaveTofile(const Player &player, const string &filename);
bool LoadFromFile(Player &player, const string &filename, const HashTable<string, Item> &itemDB);

#endif